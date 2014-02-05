#!/bin/bash

python stealth_generate.py 03_one_of_each_large/F=1 
python stealth_generate.py 03_one_of_each_large/F=2 
python stealth_generate.py 03_one_of_each_large/F=3
python stealth_generate.py 05_varying_param/F=1 
python stealth_generate.py 05_varying_param/F=2/X=10/fx=.0000001 
python stealth_generate.py 05_varying_param/F=2/X=10/fx=.25
python stealth_generate.py 05_varying_param/F=2/X=100/fx=.0000001 
python stealth_generate.py 05_varying_param/F=2/X=100/fx=.25
python stealth_generate.py 05_varying_param/F=2/X=500/fx=.0000001 
python stealth_generate.py 05_varying_param/F=2/X=500/fx=.25
python stealth_generate.py 05_varying_param/F=2/X=1000/fx=.0000001 
python stealth_generate.py 05_varying_param/F=2/X=1000/fx=.25
python stealth_generate.py 05_varying_param/F=3
python stealth_generate.py 06_large/F=1 
python stealth_generate.py 06_large/F=2 
python stealth_generate.py 06_large/F=3
python stealth_generate.py 07_one_of_each_very_large
python stealth_generate.py 08_very_large
