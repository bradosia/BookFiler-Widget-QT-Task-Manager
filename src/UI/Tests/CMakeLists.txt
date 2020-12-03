enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(
  Qt5
  COMPONENTS Widgets Test Core
  REQUIRED)
add_executable(widgettasklisttest WidgetTaskListTest.cpp)
add_test(
  NAME widgettasklisttest
  COMMAND widgettasklisttest
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_include_directories(widgettasklisttest PRIVATE ${lib_shared_name})
target_link_libraries(widgettasklisttest PRIVATE Qt5::Test ${lib_shared_name} Qt5::Widgets
                                                 sqlite3)


add_executable(widgettaskitemtest WidgetTaskItemTest.cpp)
add_test(NAME widgettaskitemtest
    COMMAND widgettaskitemtest
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
target_include_directories(widgettaskitemtest PRIVATE ${lib_shared_name} )
target_link_libraries(widgettaskitemtest PRIVATE Qt5::Test Qt5::Widgets Qt5::Core ${lib_shared_name})
