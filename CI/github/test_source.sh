#!/bin/bash

set -e
set -x

cd ../../

python -m venv test_env
source test_env/bin/activate

cd subseq/subseq

python -m pip install cython pytest
make
python setup.py install

cd ../..
# Run the tests on the installed source distribution
mkdir tmp_for_test
cp -r subseq/subseq/tests tmp_for_test
cd tmp_for_test

pytest tests
