include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(process_tree process_tree.cpp)
add_executable(context context.cpp)
add_executable(xpath xpath.cpp)

target_link_libraries(process_tree libyang_cpp)
target_link_libraries(context libyang_cpp)
target_link_libraries(xpath libyang_cpp)
