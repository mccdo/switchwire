/*************** <auto-copyright.rb BEGIN do not edit this line> **************
 *
 * Copyright 2012-2012 by Ames Laboratory
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.rb END do not edit this line> ***************/
#include <switchwire/InteractionEvent.h>


namespace switchwire
{
////////////////////////////////////////////////////////////////////////////////
InteractionEvent::InteractionEvent( eventType eType,
                                    int key,
                                    const char keyChar,
                                    const wchar_t keyUnicode,
                                    int modifiers,
                                    buttonType button,
                                    int buttons,
                                    float scrollDeltaX,
                                    float scrollDeltaZ,
                                    double x,
                                    double y,
                                    double z ):
    EventType( eType ),
    Key( key ),
    KeyChar( keyChar ),
    KeyUnicode( keyUnicode ),
    Modifiers( modifiers ),
    Button( button ),
    Buttons( buttons ),
    ScrollDeltaX( scrollDeltaX ),
    ScrollDeltaZ( scrollDeltaZ ),
    X( x ),
    Y( y ),
    Z( z )
{
   ;
}
////////////////////////////////////////////////////////////////////////////////
InteractionEvent::~InteractionEvent()
{
    ;
}
////////////////////////////////////////////////////////////////////////////////
} // namespace switchwire

