    
#Lets us address our internal includes as <switchwire/foo.h>
include_directories(
        ${CMAKE_SOURCE_DIR}/src
    )

ADD_DEFINITIONS(-DSWITCHWIRE_LIBRARY)

FILE( GLOB srcs "*.cxx" )
FILE( GLOB hdrs "*.h" )

set(VES_PRIVATE_HEADERS ${hdrs})
set(VES_PUBLIC_HEADERS ${hdrs} )

set(VES_TARGET_NAME switchwire)
set(VES_TARGET_VERSION ${switchwire_VERSION})
set(VES_TARGET_EXPORT ${CMAKE_PROJECT_NAME}-targets)
set(VES_TARGET_CATEGORY Lib)

ADD_LIBRARY(${VES_TARGET_NAME} SHARED ${srcs} ${VES_PUBLIC_HEADERS})
TARGET_LINK_LIBRARIES(${VES_TARGET_NAME} ${switchwire_LIBS} ${POCO_LIBRARIES})

include(VESModuleInstall)
