    
#Lets us address our internal includes as <eventmanager/foo.h>
include_directories(
        ${CMAKE_SOURCE_DIR}/src
    )

ADD_DEFINITIONS(-DEVENTMANAGER_LIBRARY)

FILE( GLOB srcs "*.cxx" )
FILE( GLOB hdrs "*.h" )

SET(TARGET_SRC ${srcs})
SET(PUBLIC_HEADERS ${hdrs})

SET(TARGET_NAME eventmanager)
ADD_LIBRARY(${TARGET_NAME} SHARED ${TARGET_SRC} ${PUBLIC_HEADERS})
TARGET_LINK_LIBRARIES(${TARGET_NAME} ${eventmanager_LIBS} ${POCO_LIBRARIES})

set_target_properties( ${TARGET_NAME} PROPERTIES VERSION ${switchwire_VERSION} )
set_target_properties( ${TARGET_NAME} PROPERTIES SOVERSION ${switchwire_VERSION} )
set_target_properties( ${TARGET_NAME} PROPERTIES PROJECT_LABEL "Lib ${TARGET_NAME}" )

INSTALL(TARGETS ${TARGET_NAME}
        EXPORT switchwire-targets
        RUNTIME DESTINATION ${INSTALL_BINDIR}
        LIBRARY DESTINATION ${INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR})

INSTALL(FILES       ${PUBLIC_HEADERS}
        DESTINATION ${INSTALL_INCDIR}/${TARGET_NAME})