import setuptools
from setuptools import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import sys
from os import path
import platform


if platform.system() == "Windows":
    compile_args = []
else:
    compile_args = ["-std=c++11"]

cereal_path = path.join("subseq", "cpp_sources", "_deps", "cereal-src", "include")

module = Extension(
    "*",
    [
        "subseq/*.pyx",
        "subseq/cpp_sources/Bitset.cpp",
        "subseq/cpp_sources/CSubseq.cpp",
        "subseq/cpp_sources/FmIndex.cpp",
        "subseq/cpp_sources/FrequencyArray.cpp",
        "subseq/cpp_sources/WaveletTree.cpp",
        "subseq/cpp_sources/SubqueryGenerator.cpp",
    ],
    include_dirs=[cereal_path],
    language="c++",
    extra_compile_args=compile_args,
    extra_link_args=compile_args,
)

version = "1.0.3"

author = "Bluesheeptoken"
author_email = "louis.fruleux1@gmail.com"

description = "Succinct BWT-Based SequencePrediction"

license = "MIT"

this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, "README.md")) as f:
    long_description = f.read()

url = "https://github.com/bluesheeptoken/subseq"

setup(
    name="subseq",
    ext_modules=cythonize(
        module,
        annotate=False,
        compiler_directives={"language_level": sys.version_info[0]},
    ),
    version=version,
    author=author,
    author_email=author_email,
    description=description,
    license=license,
    long_description=long_description,
    long_description_content_type="text/markdown",
    url=url,
    python_requires=">=3.7, <4"
)
