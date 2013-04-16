#Lets us address our internal includes as <switchwire/foo.h>

configure_file( "${PROJECT_SOURCE_DIR}/src/switchwire/Version.h.in" "${PROJECT_SOURCE_DIR}/src/switchwire/Version.h" @ONLY)

if(Squirrel_FOUND AND Sqrat_FOUND)
    add_subdirectory(squirrel)
endif(Squirrel_FOUND AND Sqrat_FOUND)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
    )

ADD_DEFINITIONS(-DSWITCHWIRE_LIBRARY)

FILE( GLOB srcs "*.cxx" )
FILE( GLOB hdrs "*.h" )

list( APPEND srcs ${squirrel_hdrs} )

set(VES_PRIVATE_HEADERS ${hdrs})
set(VES_PUBLIC_HEADERS ${hdrs} )

set(VES_TARGET_NAME switchwire)
set(VES_TARGET_VERSION ${switchwire_VERSION})
set(VES_TARGET_EXPORT ${PROJECT_NAME}-targets)
set(VES_TARGET_CATEGORY Lib)

ADD_LIBRARY(${VES_TARGET_NAME} SHARED ${srcs} ${VES_PUBLIC_HEADERS})
TARGET_LINK_LIBRARIES(${VES_TARGET_NAME} ${switchwire_LIBS} ${POCO_LIBRARIES})

include(VESModuleInstall)

