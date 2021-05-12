set(SOURCE_EXE
tests.cpp
)

add_executable(HASH_test ${SOURCE_EXE})

target_link_libraries(HASH_test PUBLIC HASH_lib)

target_link_libraries(HASH_test PUBLIC gtest_main)

set_property(TARGET HASH_test PROPERTY FOLDER "HASH_test")
