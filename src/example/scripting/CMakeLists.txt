#Lets us address our internal includes as <switchwire/foo.h>
include_directories(
        ${PROJECT_SOURCE_DIR}/src
    )

####### ExplicitSignalBinding (ExplicitSignalBinding.cxx) #######
SET(TARGET_SRC ExplicitSignalBinding.cxx)
SET(TARGET_NAME ExplicitSignalBinding)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire ${Squirrel_LIBRARY} ${Squirrel_STD_LIBRARY})

SET(INSTALL_BINDIR bin/scripting)

INSTALL(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${INSTALL_BINDIR}
)

####### ExplicitSlotBinding (ExplicitSlotBinding.cxx) #######
SET(TARGET_SRC ExplicitSlotBinding.cxx)
SET(TARGET_NAME ExplicitSlotBinding)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire ${Squirrel_LIBRARY} ${Squirrel_STD_LIBRARY})

SET(INSTALL_BINDIR bin/scripting)

INSTALL(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${INSTALL_BINDIR}
)

####### ReceiveEvent (ReceiveEvent.cxx) #######
SET(TARGET_SRC ReceiveEvent.cxx)
SET(TARGET_NAME ReceiveEvent)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire ${Squirrel_LIBRARY} ${Squirrel_STD_LIBRARY})

SET(INSTALL_BINDIR bin/scripting)

INSTALL(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${INSTALL_BINDIR}
)

####### SendEvent (SendEvent.cxx) #######
SET(TARGET_SRC SendEvent.cxx)
SET(TARGET_NAME SendEvent)
ADD_EXECUTABLE(${TARGET_NAME} ${TARGET_SRC})
TARGET_LINK_LIBRARIES(${TARGET_NAME} switchwire ${Squirrel_LIBRARY} ${Squirrel_STD_LIBRARY})

SET(INSTALL_BINDIR bin/scripting)

INSTALL(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${INSTALL_BINDIR}
)

####### Sample squirrel scripts #######
install(FILES ReceiveInt.nut SendInt.nut ExplicitSendInt.nut ExplicitReceiveInt.nut
    DESTINATION bin/scripting
    COMPONENT development)
