#Lets us address our internal includes as <switchwire/foo.h>
include_directories(
        ${CMAKE_SOURCE_DIR}/src
    )

FILE( GLOB srcs "*.cxx" )
FILE( GLOB hdrs "*.h" )

SET(TARGET_SRC ${srcs})
SET(PUBLIC_HEADERS ${hdrs})

SET(TARGET_NAME switchwireTest)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire )


SET(INSTALL_BINDIR bin)

INSTALL(
        TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
    )

