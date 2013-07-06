#Lets us address our internal includes as <switchwire/foo.h>

configure_file( "${PROJECT_SOURCE_DIR}/src/switchwire/Version.h.in" "${PROJECT_SOURCE_DIR}/src/switchwire/Version.h" @ONLY)

if(Squirrel_FOUND AND Sqrat_FOUND)
    add_subdirectory(squirrel)
endif(Squirrel_FOUND AND Sqrat_FOUND)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
    )

add_definitions(-DSWITCHWIRE_LIBRARY)

FILE( GLOB srcs "*.cxx" )
FILE( GLOB hdrs "*.h" )

list( APPEND srcs ${squirrel_hdrs} )

set(VES_PRIVATE_HEADERS ${hdrs})
set(VES_PUBLIC_HEADERS ${hdrs} )

set(VES_TARGET_NAME switchwire)
set(VES_TARGET_VERSION ${switchwire_VERSION})
set(VES_TARGET_EXPORT ${PROJECT_NAME}-targets)
set(VES_TARGET_CATEGORY Lib)

add_library(${VES_TARGET_NAME} SHARED ${srcs} ${VES_PUBLIC_HEADERS})
target_link_libraries(${VES_TARGET_NAME} LINK_PUBLIC ${POCO_LIBRARIES})

if(Squirrel_FOUND AND Sqrat_FOUND AND NOT MSVC)
    if(APPLE)
        set(squirrel_static_lib "-Wl,-all_load ${Squirrel_LIBRARY}")
        set(squirrel_std_static_lib "-Wl,-all_load ${Squirrel_STD_LIBRARY}")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        set(squirrel_static_lib "-Wl,-whole-archive ${Squirrel_LIBRARY} -Wl,-no-whole-archive")
        set(squirrel_std_static_lib "-Wl,-whole-archive ${Squirrel_STD_LIBRARY} -Wl,-no-whole-archive")
    endif()
    target_link_libraries(${VES_TARGET_NAME} LINK_PRIVATE ${squirrel_static_lib} ${squirrel_std_static_lib})
endif()

include(VESModuleInstall)

