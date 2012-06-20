SET(    bong_qt_SRC
        translatable.cpp
        dtdfiletype.cpp
        propertiesfiletype.cpp
    )

SET(    bong_qt_HEADERS
        translatable.h
        dtdfiletype.h
        propertiesfiletype.h
        bong_qt_export.h
   )

qt4_wrap_cpp(bong_qt_MOC ${bong_qt_HEADERS})
add_library(bong_qt SHARED ${bong_qt_SRC} ${bong_qt_MOC})
target_link_libraries(bong_qt ${QT_QTCORE_LIBRARY})

set_target_properties(bong_qt PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_BONG_QT)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

include(CheckCXXCompilerFlag)

if (CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    check_cxx_compiler_flag(-fvisibility=hidden _HAVE_GCC_VISIBILITY)
    if (_HAVE_GCC_VISIBILITY)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

        check_cxx_compiler_flag(-fvisibility-inlines-hidden _HAVE_GCC_VISIBILITY_INLINES)
        if (_HAVE_GCC_VISIBILITY_INLINES)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
        endif (_HAVE_GCC_VISIBILITY_INLINES)
    endif (_HAVE_GCC_VISIBILITY)
endif (CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)

install( TARGETS bong_qt DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         ${bong_qt_HEADERS}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bong-qt COMPONENT devel
         )

set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include/bong-qt)
get_target_property(LIB_OUT_NAME bong_qt LOCATION)
get_filename_component(LIB_OUT_NAME ${LIB_OUT_NAME} NAME)
set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

configure_file(
   BongQtConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BongQtConfig.cmake @ONLY
)

install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/BongQtConfig.cmake
	 DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/BongQt
)



