#!/bin/bash

set -e
set -x

if [[ "$RUNNER_OS" == "macOS" ]]; then
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
fi

python -m pip install cibuildwheel==2.11.1
python -m cibuildwheel --output-dir wheelhouse
