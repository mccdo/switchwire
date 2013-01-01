#Lets us address our internal includes as <switchwire/foo.h>
include_directories(
        ${CMAKE_SOURCE_DIR}/src
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


####### Scripting (scripting.cxx) #######
# Commented out for now until we setup installers and find modules for
# squirrel and sqrat
#SET(TARGET_SRC scripting.cxx)
#SET(TARGET_NAME Scripting)
#ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
#TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire /home/penn/deps/SQUIRREL3/lib/libsquirrel.a /home/penn/deps/SQUIRREL3/lib/libsqstdlib.a)
#
#SET(INSTALL_BINDIR bin)
#
#INSTALL(
#        TARGETS ${TARGET_NAME}
#        RUNTIME DESTINATION ${INSTALL_BINDIR}
#    )

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

####### Sample squirrel script #######
install(FILES printAnInt.nut
    DESTINATION bin/scripts
    COMPONENT development)
