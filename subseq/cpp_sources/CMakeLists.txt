include(FetchContent)

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


FetchContent_Declare(
  cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal.git
  GIT_TAG        ebef1e929807629befafbb2918ea1a08c7194554 # release-1.3.2
)

set(SKIP_PERFORMANCE_COMPARISON ON)

FetchContent_GetProperties(cereal)
if(NOT cereal_POPULATED)
  FetchContent_Populate(cereal)
  add_subdirectory(${cereal_SOURCE_DIR} ${cereal_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_MakeAvailable(
  cereal
)

target_link_libraries(subseq_cpp cereal::cereal)
