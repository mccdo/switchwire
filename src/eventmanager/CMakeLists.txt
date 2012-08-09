    
#Lets us address our internal includes as <eventmanager/foo.h>
include_directories(
        ${CMAKE_SOURCE_DIR}/src
    )

#Lets us know we're building the library so export definition can be set up
#correctly for win32
#IF(WIN32)
ADD_DEFINITIONS(-DEVENTMANAGER_LIBRARY)
#ENDIF (WIN32)

FILE( GLOB srcs "*.cxx" )
FILE( GLOB hdrs "*.h" )

SET(TARGET_SRC ${srcs})
SET(PUBLIC_HEADERS ${hdrs})

SET(TARGET_NAME eventmanager)
ADD_LIBRARY(${TARGET_NAME} SHARED ${TARGET_SRC} ${PUBLIC_HEADERS})
TARGET_LINK_LIBRARIES(${TARGET_NAME} ${eventmanager_LIBS} ${POCO_LIBRARIES})

SET(INSTALL_INCDIR include)
SET(INSTALL_BINDIR bin)
    SET(INSTALL_ARCHIVEDIR ${CMAKE_INSTALL_LIBDIR})
IF(WIN32)
    SET(INSTALL_LIBDIR bin)
ELSE()
    SET(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
ENDIF()

set_target_properties( ${TARGET_NAME} PROPERTIES VERSION ${switchwire_VERSION} )
set_target_properties( ${TARGET_NAME} PROPERTIES SOVERSION ${switchwire_VERSION} )
set_target_properties( ${TARGET_NAME} PROPERTIES PROJECT_LABEL "Lib ${TARGET_NAME}" )

INSTALL(
        TARGETS ${TARGET_NAME}
        EXPORT switchwire-targets
        RUNTIME DESTINATION ${INSTALL_BINDIR}
        LIBRARY DESTINATION ${INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR}
    )

INSTALL(
        FILES       ${PUBLIC_HEADERS}
        DESTINATION ${INSTALL_INCDIR}/${TARGET_NAME}
    )
