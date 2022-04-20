#!/bin/bash

set -e
set -x

# Move up two levels to create the virtual
# environment outside of the source folder
cd ../../

python -m venv build_env
source build_env/bin/activate

python -m pip install cython
python -m pip install twine

cd subseq/subseq
make
python setup.py sdist

# Check whether the source distribution will render correctly
twine check dist/*.tar.gz
