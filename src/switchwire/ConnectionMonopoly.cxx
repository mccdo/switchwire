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
#include <switchwire/ConnectionMonopoly.h>


namespace switchwire
{

ConnectionMonopoly::ConnectionMonopoly( )
{
}

ConnectionMonopoly::~ConnectionMonopoly( )
{
    // When this object is destroyed, mBlockers will go out of scope, which should
    // cause all the shared pointers to shared_connection_block(s) to go out of
    // scope and autodelete.
}

void ConnectionMonopoly::AddBlocker( boost::shared_ptr< boost::signals2::shared_connection_block > blocker )
{
    mBlockers.push_back( blocker );
}

}

