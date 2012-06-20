include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR})

set(test1_SRCS test1.cpp)
qt4_automoc(${prison_SRCS})
add_executable(bong-qt-test1 ${test1_SRCS})
target_link_libraries(bong-qt-test1 ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})