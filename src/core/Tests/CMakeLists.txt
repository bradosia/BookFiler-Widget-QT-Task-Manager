enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(
  Qt5
  COMPONENTS Test Core
  REQUIRED)
add_executable(sqliteenginetest sqliteenginetest.cpp)
add_test(
  NAME sqliteenginetest
  COMMAND sqliteenginetest
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_include_directories(sqliteenginetest PRIVATE ${lib_shared_name})
target_link_libraries(sqliteenginetest PRIVATE Qt5::Test ${lib_shared_name}
                                               sqlite3)
