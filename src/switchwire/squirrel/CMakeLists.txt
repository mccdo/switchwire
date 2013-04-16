#Lets us address our internal includes as <switchwire/foo.h>

set( _destDir include/switchwire/squirrel )

FILE( GLOB hdrs "*.h" )

install(FILES ${hdrs}
    DESTINATION ${_destDir}
    COMPONENT development)
    
if( MSVC )
    source_group( "Squirrel" FILES ${hdrs} )
    set_source_files_properties( ${hdrs} PROPERTIES HEADER_FILE_ONLY  TRUE)
endif()

set(squirrel_hdrs "${hdrs}" PARENT_SCOPE)
