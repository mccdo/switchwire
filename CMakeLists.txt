cmake_minimum_required (VERSION 2.8.8)

project( switchwire )

SET( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" )

set(switchwire_MAJOR_VERSION 0)
set(switchwire_MINOR_VERSION 2)
set(switchwire_SUB_VERSION 0)
set(switchwire_VERSION ${switchwire_MAJOR_VERSION}.${switchwire_MINOR_VERSION}.${switchwire_SUB_VERSION})
set(VES_PACKAGE_VERSION ${switchwire_VERSION})

set( POCO_ROOT "Please specify" CACHE PATH "Root directory where POCO is installed" )
FIND_PACKAGE(POCO 1.4.1 REQUIRED COMPONENTS PocoFoundation PocoUtil PocoData PocoDataSQLite)

set(BOOST_INCLUDEDIR "$ENV{BOOST_INSTALL_DIR}/include" CACHE PATH "docstring")

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost 1.44.0 REQUIRED COMPONENTS system)

INCLUDE_DIRECTORIES( 
    ${Boost_INCLUDE_DIRS}
    ${POCO_INCLUDE_DIR}
)

SET( CMAKE_BUILD_TYPE RelWithDebInfo )

option(BUILD_EXAMPLE "Build example?" ON)

################################################################################
# Platform specific definitions
IF(WIN32)
    IF(MSVC)
        # To enable /MP, parralel build on MSVC
        OPTION(WIN32_USE_MP "Set to OFF to diable /MP." ON)
        MARK_AS_ADVANCED(WIN32_USE_MP)
        IF(WIN32_USE_MP)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        ENDIF(WIN32_USE_MP)

        # Other MSVC compilation flags
        #ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
        #ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)

    ENDIF(MSVC)
ENDIF (WIN32)

include(VESBinAndLibDirs)

add_subdirectory(src)

#
# Doxygen
#find_package( Doxygen )
#if( DOXYGEN_FOUND )
#    set( HAVE_DOT "NO" )
#    if( DOXYGEN_DOT_PATH )
#        set( HAVE_DOT "YES" )
#    endif()
#    
#    configure_file( ${PROJECT_SOURCE_DIR}/doc/doxyfile.cmake
#        ${PROJECT_BINARY_DIR}/doc/doxyfile
#    )
#    add_custom_target( Documentation ${DOXYGEN_EXECUTABLE}
#        ${PROJECT_BINARY_DIR}/doc/doxyfile
#    )
#    
#    add_subdirectory( doc/images )
#endif()

include(VESInstallPDBFiles)

set(VES_EXPORT_LIBRARY_TARGETS switchwire)
set(VES_CONFIGURE_VARS CMAKE_INSTALL_LIBDIR)

#
# Setup the fpc auto detection files
if(WIN32)
    set(switchwire_FPC_LIBRARIES "/libpath:\"\${libdir}\" switchwire.lib")
    set(switchwire_FPC_INCLUDES "/I\"\${includedir}\"")
else(WIN32)
    set(switchwire_FPC_INCLUDES "-I\${includedir}")
    set(switchwire_FPC_LIBRARIES "-L\${libdir} -lswitchwire")
endif(WIN32)

include(VESInstallAutoDiscoveryTools)
