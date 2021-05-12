set(SOURCE_LIB
hash_library.cpp
hash_library.hpp
)

add_library(HASH_lib STATIC ${SOURCE_LIB})

target_include_directories(HASH_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCE_LIB})

set_property(TARGET HASH_lib PROPERTY FOLDER "myhash_lib")

add_subdirectory(tests)