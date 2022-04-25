BUILD_DIR=build
SRC_DIR=subseq
CPP_SRC_DIR=subseq/cpp_sources
PYTHON_TEST_DIR=tests
CPP_TEST_BUILD_DIR=test_build

.PHONY: build tests tests_cpp

build: cmake_cpp_sources
	make -C ${CPP_SRC_DIR}
	python3 setup.py build_ext --inplace

clean:
	rm -rf ${BUILD_DIR}/
	rm -f ${SRC_DIR}/*.cpp

cmake_cpp_sources:
	cmake ${CPP_SRC_DIR} -B ${CPP_SRC_DIR}

lint: lint_cpp lint_python

lint_cpp: cmake_cpp_sources
	make -C ${CPP_SRC_DIR} clang-format
	make -C ${CPP_SRC_DIR} clang-tidy

lint_python:
	black ${PYTHON_TEST_DIR}

lint_check: cmake_cpp_sources
	make -C ${CPP_SRC_DIR} clang-format-check
	black --check ${PYTHON_TEST_DIR}

test: test_cpp test_python

test_python: build
	pytest tests

test_cpp:
	mkdir -p ${CPP_TEST_BUILD_DIR}
	cmake -B ${CPP_TEST_BUILD_DIR} -S .
	make -C ${CPP_TEST_BUILD_DIR}
	make -C ${CPP_TEST_BUILD_DIR} test ARGS='-VV'
