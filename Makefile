BUILD_DIR=build
SRC_DIR=subseq
CPP_SRC_DIR=subseq/cpp_sources
PYTHON_TEST_DIR=test
CPP_TEST_BUILD_DIR=test_build

.PHONY: build test test_cpp

build:
	python3 setup.py build_ext --inplace

clean:
	rm -rf ${BUILD_DIR}/
	rm -f ${SRC_DIR}/*.cpp

cmake_cpp_sources:
	cmake ${CPP_SRC_DIR} -B ${CPP_SRC_DIR}
lint: lint_cpp lint_python

lint_check: cmake_cpp_sources
	make -C ${CPP_SRC_DIR} clang-format-check
	black --check ${PYTHON_TEST_DIR}

test: test_cpp test_python

test_python: build
	pytest test

test_cpp:
	mkdir -p ${CPP_TEST_BUILD_DIR}
	cmake -B ${CPP_TEST_BUILD_DIR} -S .
	make -C ${CPP_TEST_BUILD_DIR}
	make -C ${CPP_TEST_BUILD_DIR} test ARGS='-VV'
