cmake_minimum_required (VERSION 2.8.8)

project( switchwire )

SET( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" )

set(switchwire_MAJOR_VERSION 0)
set(switchwire_MINOR_VERSION 2)
set(switchwire_SUB_VERSION 0)
set(switchwire_VERSION ${switchwire_MAJOR_VERSION}.${switchwire_MINOR_VERSION}.${switchwire_SUB_VERSION})
set(VES_PACKAGE_VERSION ${switchwire_VERSION})

#Set the include directory so that switchwire can be used as a sub project
if( NOT(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME}) )
    set(switchwire_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src" PARENT_SCOPE)
    set(switchwire_LIBRARIES "switchwire" PARENT_SCOPE)
endif()

set( POCO_ROOT "Please specify" CACHE PATH "Root directory where POCO is installed" )
FIND_PACKAGE(POCO 1.4.1 REQUIRED COMPONENTS PocoFoundation PocoUtil PocoXML PocoData PocoDataSQLite)

set(BOOST_INCLUDEDIR "$ENV{BOOST_INSTALL_DIR}/include" CACHE PATH "docstring")

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost 1.44.0 REQUIRED COMPONENTS system)

set( Squirrel_ROOT "Please specify" CACHE PATH "Root directory where Squirrel is installed" )
FIND_PACKAGE(Squirrel 3.0.0)

set( Sqrat_ROOT "Please specify" CACHE PATH "Root directory where Sqrat is installed" )
FIND_PACKAGE(Sqrat 0.8)

INCLUDE_DIRECTORIES( 
    ${Boost_INCLUDE_DIRS}
    ${POCO_INCLUDE_DIR}
)

if(Squirrel_FOUND AND Sqrat_FOUND)
    INCLUDE_DIRECTORIES( 
        ${Sqrat_INCLUDE_DIR}
        ${Squirrel_INCLUDE_DIR}
    )
endif(Squirrel_FOUND AND Sqrat_FOUND)

set(HAVE_SQUIRREL 0)
if(Squirrel_FOUND)
    set(HAVE_SQUIRREL 1)
endif(Squirrel_FOUND)
#SET( CMAKE_BUILD_TYPE RelWithDebInfo )

option(BUILD_EXAMPLE "Build example?" ON)

include(VESSetupCompiler)

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

set(CPACK_PACKAGE_VENDOR "Ames Lab")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A library for boosts signals and slots.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.txt") 
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/README.txt") 
set(CPACK_PACKAGE_VERSION_MAJOR "${switchwire_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${switchwire_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${switchwire_SUB_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}_${VES_PACKAGE_VERSION}")
#This sits right below CPACK_PACKAGE_DEFAULT_LOCATION
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
#set(CPACK_TOPLEVEL_TAG "${PROJECT_NAME}")
#set(CPACK_SET_DESTDIR TRUE)
if(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  set(CPACK_NSIS_MODIFY_PATH ON)
  set(CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable")
else(WIN32 AND NOT UNIX) 
  #This directory is the prefix to the default install prefix
  set(CPACK_PACKAGE_DEFAULT_LOCATION "/opt/${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  set(CPACK_STRIP_FILES OFF)
  set(CPACK_SOURCE_STRIP_FILES OFF)
endif(WIN32 AND NOT UNIX)

include(CPack)
