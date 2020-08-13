from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import sys
from os import path


compile_args = ['-std=c++11']

module = Extension('*',
        ['subseq/*.pyx',
        'subseq/cpp_sources/Bitset.cpp',
        'subseq/cpp_sources/CSubseq.cpp',
        'subseq/cpp_sources/FmIndex.cpp',
        'subseq/cpp_sources/FrequencyArray.cpp',
        'subseq/cpp_sources/WaveletTree.cpp',
        'subseq/cpp_sources/SubqueryGenerator.cpp',
        ],
        language="c++",
        extra_compile_args=compile_args,
        extra_link_args=compile_args
)

setup(name="subseq",
      ext_modules=cythonize(
        module,
        annotate=False,
        compiler_directives={'language_level': sys.version_info[0]})
)

