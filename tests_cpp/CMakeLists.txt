add_executable(
    unit_tests
    BitsetTest.cpp
    WaveletTreeTest.cpp
    FmIndexTest.cpp
    CSubseqTest.cpp
    FrequencyArrayTest.cpp
    SubqueryGeneratorTest.cpp
)

target_link_libraries(
    unit_tests
    gtest_main
    subseq_cpp
)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
