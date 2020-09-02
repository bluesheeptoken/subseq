project(subseq_cpp)

add_library(subseq_cpp "")

target_sources(
    subseq_cpp
    PRIVATE
        Bitset.cpp
        WaveletTree.cpp
        FmIndex.cpp
        CSubseq.cpp
        FrequencyArray.cpp
        SubqueryGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Bitset.hpp
        ${CMAKE_CURRENT_LIST_DIR}/WaveletTree.hpp
        ${CMAKE_CURRENT_LIST_DIR}/FmIndex.hpp
        ${CMAKE_CURRENT_LIST_DIR}/CSubseq.hpp
        ${CMAKE_CURRENT_LIST_DIR}/FrequencyArray.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SubqueryGenerator.hpp
)

target_include_directories(
    subseq_cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

include(cmake/clang-cxx-dev-tools.cmake)
