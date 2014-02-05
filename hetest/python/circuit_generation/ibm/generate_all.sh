#!/bin/bash

python ibm_generate.py 03_one_of_each_large/K=80 
python ibm_generate.py 03_one_of_each_large/K=128
python ibm_generate.py 05_varying_param/K=80 
python ibm_generate.py 05_varying_param/K=128
python ibm_generate.py 06_large/K=80 
python ibm_generate.py 06_large/K=128
python ibm_generate.py 07_additional/K=80 
python ibm_generate.py 07_additional/K=128
