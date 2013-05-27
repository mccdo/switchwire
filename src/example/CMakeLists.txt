#Lets us address our internal includes as <switchwire/foo.h>
include_directories(
        ${PROJECT_SOURCE_DIR}/src
    )

#FILE( GLOB srcs "*.cxx" )
#FILE( GLOB hdrs "*.h" )

####### switchwireTest (main.cxx) #######
SET(TARGET_SRC main.cxx)
SET(PUBLIC_HEADERS ${hdrs})

SET(TARGET_NAME switchwireTest)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire )


SET(INSTALL_BINDIR bin)

INSTALL(
        TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
    )


####### Scripting sudbir #######
if(Squirrel_FOUND AND Sqrat_FOUND)
    add_subdirectory( scripting )
endif(Squirrel_FOUND AND Sqrat_FOUND)

####### BasicStatic (BasicStatic.cxx) #######
SET(TARGET_SRC BasicStatic.cxx)
SET(TARGET_NAME BasicStatic)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire)

SET(INSTALL_BINDIR bin)

INSTALL(
        TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
    )

####### BasicClass (BasicClass.cxx) #######
SET(TARGET_SRC BasicClass.cxx)
SET(TARGET_NAME BasicClass)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire)

SET(INSTALL_BINDIR bin)

INSTALL(
        TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
    )
