from SCons.Script import *
import tempfile
import sys
import os.path
import multiprocessing

# This sets up the environment. All the SConstruct files should use this.
env = DefaultEnvironment()

# Command line flags here determine debug and release build info. This info is
# propagated down to the language-specific builders which then set compiler
# flags and such as appropriate.
AddOption('--opt', dest='opt', action='store_true', default=False, 
        help='Optimized build')
AddOption('--test_to_err', dest='test_to_err', action='store_true',
        default=False, help = 'Send unit test output to stderr '
        'instead of in a temporary file')

# If the user has not specified -j or --jobs we will figure out the number of
# available CPUs and run that many parallel jobs. To disable the user can
# specify -j to limit the cpu count.
num_cores = multiprocessing.cpu_count()
env.SetOption('num_jobs', num_cores)
if env.GetOption('num_jobs') == num_cores:
    print 'Running with -j %s. Specify -j or --jobs to override.' % num_cores

class UnitTestRunner(object):
    """There is one object of this class for each unit test that we are going to
    run. The class variables keep track of the total number of tests and the
    total number that have passed and failed. When all tests have run a summary
    is printed out."""
    num_tests = 0
    num_success = 0
    num_fail = 0
    def __init__(self, test_fun, test_target, kwargs):
        """This will run a unit test by calling test_fun with test_target
        and a log file path as arguments. test_fun must be a function that
        returns True if the test passes and False otherwise. It should write any
        test output to the passed log file so users can look at the test
        output.
        
        Arguments:
            test_fun: a function that accepts a target, a log file, and any
                optional kwargs as input, runs a test and returns true iff the
                test passes.
            test_target: the target that should be passed to test_fun
            kwargs: An optional dict that will be passed to test_fun
                as **kwargs
        """
        self.__test_target = test_target
        self.__test_fun = test_fun
        self.__kwargs = kwargs
        UnitTestRunner.num_tests += 1

    def run(self, target = None, source = None, env = None):
        """This runs the test using the arguments passed to __init__. The
        arguments the method takes are meaningless - they are only here because
        this is wrapped up as a scons Action and Action functions must accept
        these arguments."""
        LINE_LENGTH = 70
        if GetOption('test_to_err'):
            log_file = sys.stderr
        else:
            log_file = tempfile.NamedTemporaryFile(delete=False)
        running_str = ("Test: %s. Output: %s. Result: " %
                (self.__test_target, log_file.name))

        ret = self.__test_fun(self.__test_target, log_file, **self.__kwargs)
        if ret == 0:
            success_fail_str = 'SUCCCESS'
            UnitTestRunner.num_success += 1
        else:
            success_fail_str = 'FAILED'
            UnitTestRunner.num_fail += 1
        print '%s [%s]\n' % (running_str, success_fail_str)
        sys.stdout.flush()

        tests_run = UnitTestRunner.num_fail + UnitTestRunner.num_success 
        if tests_run == UnitTestRunner.num_tests:
            self.print_summary()

    @classmethod
    def print_summary(cls):
        if cls.num_success == cls.num_tests:
            print '\n\n%s Tests Passed. None Failed. SUCCESS!\n' % cls.num_tests
        else:
            print '\n\n%s of %s Tests FAILED.' % (cls.num_fail, cls.num_tests)

class GenericTestBuilder(object):
    """scons Builder objects are kind of a pain and don't quite work right. This
    class does not, in fact, create a builder but it makes it *seem* as if it
    does. To use construct an object of this class passing the builder_name and
    the other options as specified in __init__. This will attach a method with
    the builder name to the environment and it can be used like a builder that
    runs unit tests.
    
    Using this "builder" creates 3 aliases for every test added via a call to
    __add_test:
        
        1) The alias passed to __add_test can be used to run just that one test.
        2) The alis passed to __init__ can be used to run all tests constructed
           via this object. 
        3) The alias "test" can be used to run all tests added via any
           GenericTestBuilder.
    
    See the BUILD.README for more info."""
    # Every time you construct a new instance of this class it adds itself to
    # this list. Then when you call create_all_targets it uses this list to
    # create all the aliases.
    all_builders = []
    TEST_PROG_PREFIX = 'test_prg_'

    def __init__(self, alias_name, builder_name, test_fun):
        """Creates a builder like method so that a call to env.builder_name(foo)
        will create a test target alias to run the unit test foo. foo is assumed
        to be a target and the unit test depends on that target first being
        built.

        Arguments:
            alias_name: all unit tests added to this builder can be run via this
                alias. For example, the java/SConscript file uses an instances
                of this class with alias_name == "java_test" so that all java
                tests can be run via that alias.
            builder_name: The "builder" function added to the environment will
                have this name.
            test_fun: The test function that will called to actually run the
                unit tests.
        """
        self.tests_alias = alias_name
        self.all_tests = []
        self.builder_name = builder_name
        self.test_fun = test_fun
        GenericTestBuilder.all_builders.append(self)
        self.setup_builder()

    def __add_test(self, env, alias, target, deps, **kwargs):
        """The "builder" method calls this to schedule a test to run and
        properly set up the dependencies.
        
        Arguments:
            env: This method gets attached to the environment so it appears to
                be a builder. The environment is thus automatically passed
                though it is not used.
            alias: The name of the resulting target. For example, if you pass
                "foo" here "scons foo" would cause this test to be run.
            target: The target that gets passed to the test function supplied to
                the constructor. For C++ tests this is the path to the test
                executable, for Java tests its the name of the test class, etc.
            deps: An iterable of targets that must be built before this test can
                be run. If there is only a single dependancy you can pass it
                alone rather than wrap it in a list or tuple. You can also pass
                None if there are no dependancies (e.g. Python tests)
            kwargs: Any additional keyword arguments that should be passed to
                the test function.
        """
        # Create a UnitTestRunner object to run the test for this target.
        test_runner = UnitTestRunner(self.test_fun, target, kwargs)

        # To make this work with scons you must first wrap up the function
        # in an Action, then wrap that function in an Alias since Actions
        # can't have dependencies or be set to run. Then we specify that the
        # Alias has a depencency with target so we make sure the unit test
        # gets built before its run. Finally we specify that our alias
        # should always run otherwise scons will note that none of its
        # depenancies have changed so it won't run it.
        test_act = Action(test_runner.run, 'Running ' + str(target))
        test_alias = env.Alias(alias, deps, test_act)
        env.AlwaysBuild(test_alias)
        self.all_tests.append(test_alias)

    def setup_builder(self):
        """Adds the __add_test method to the environment with the builder_name
        specified in the constructor. For all intentes an purposes this creates
        a builder with the specified name."""
        env.AddMethod(self.__add_test, self.builder_name)


    @classmethod
    def create_all_targets(cls):
        """This should be called after all SConscript files have been sourced.
        This goes through all of the individual GenericTestBuilder objects and
        creates their target aliases and the global test alias."""
        all_tests = []
        for bldr in cls.all_builders:
            alias = Alias(bldr.tests_alias, bldr.all_tests)
            AlwaysBuild(alias)
            all_tests.append(alias)

        alias = Alias('test', all_tests)
        AlwaysBuild(alias)

