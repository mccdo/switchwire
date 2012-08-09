cmake_minimum_required (VERSION 2.8.8)

project( switchwire )

SET( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" )

set(switchwire_MAJOR_VERSION 0)
set(switchwire_MINOR_VERSION 2)
set(switchwire_SUB_VERSION 0)
set(switchwire_VERSION ${switchwire_MAJOR_VERSION}.${switchwire_MINOR_VERSION}.${switchwire_SUB_VERSION})

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

if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32 AND NOT APPLE)
    include(GNUInstallDirs)
endif(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32 AND NOT APPLE)

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR lib)
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)

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

# On windows provide the user with the pdb files 
# for debugging if they are present
if(MSVC)
    install(
        DIRECTORY ${PROJECT_BINARY_DIR}/lib/\${CMAKE_INSTALL_CONFIG_NAME}/
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        USE_SOURCE_PERMISSIONS
        COMPONENT Development
        FILES_MATCHING PATTERN "*.pdb"
    )
endif(MSVC)

# Install the CMake find script for switchwire
install( FILES "extra/Findswitchwire.cmake"
    DESTINATION "share/${CMAKE_PROJECT_NAME}/extra"
    COMPONENT Development
)

#
# Create and install all of the auto find tools
# =============================================

# Add all targets to the build-tree export set
export(TARGETS eventmanager
  FILE "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireLibraryDepends.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE switchwire)

# Create a switchwireBuildTreeSettings.cmake file for the use from the build tree
configure_file(switchwireBuildTreeSettings.cmake.in
  "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireBuildTreeSettings.cmake" @ONLY)

#configure_file(switchwireConfig.cmake.in
#  "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireConfig.cmake" @ONLY)
configure_file(switchwireConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireConfigVersion.cmake" @ONLY)
configure_file(Useswitchwire.cmake.in
  "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/Useswitchwire.cmake" @ONLY)

# Install the export set for use with the install-tree
install(EXPORT switchwire-targets DESTINATION ${CMAKE_INSTALL_LIBDIR})

include( CMakePackageConfigHelpers )
# Create the switchwireConfig.cmake and switchwireConfigVersion files
file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
   "${CMAKE_INSTALL_PREFIX}/include")

configure_package_config_file( 
    switchwireConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PATH_VARS CONF_REL_INCLUDE_DIR )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireConfig.cmake 
              ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/switchwireConfigVersion.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/Useswitchwire.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR} )

#
# Setup the fpc auto detection files
if(WIN32)
    set(switchwire_FPC_LIBRARIES "/libpath:\"\${libdir}\" eventmanager.lib")
    set(switchwire_FPC_INCLUDES "/I\"\${includedir}\"")
else(WIN32)
    set(switchwire_FPC_INCLUDES "-I\${includedir}")
    set(switchwire_FPC_LIBRARIES "-L\${libdir} -leventmanager")
endif(WIN32)

configure_file(extra/switchwire.fpc.in
  "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/flagpoll/switchwire.fpc" @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/flagpoll/switchwire.fpc
        DESTINATION lib/flagpoll )


