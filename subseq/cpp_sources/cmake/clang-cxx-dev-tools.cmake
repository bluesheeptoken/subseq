# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB
     ALL_CXX_SOURCE_FILES
     *.[ch]pp
    )

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT}
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
    --verbose
  )

  # Heavily inspired from https://gitlab.cern.ch/proteus/proteus/-/commit/8d906a45801c03832531e243f41f5f5a83177de0
  add_custom_target(
    clang-format-check
    COMMAND ${CLANG_FORMAT}
    -style=file
    -output-replacements-xml
    ${ALL_CXX_SOURCE_FILES}
    # print output
    | tee ${CMAKE_BINARY_DIR}/check_format_file.txt | grep -c "replacement " |
      tr -d "[:cntrl:]" && echo " replacements necessary"
    # WARNING: fix to stop with error if there are problems
    COMMAND ! grep -c "replacement "
      ${CMAKE_BINARY_DIR}/check_format_file.txt > /dev/null
    COMMENT "Checking format compliance"
  )

endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  add_custom_target(
    clang-tidy
    COMMAND clang-tidy
    ${ALL_CXX_SOURCE_FILES}
    -config=''
    --
    -std=c++11
    ${INCLUDE_DIRECTORIES}
    )
endif()

