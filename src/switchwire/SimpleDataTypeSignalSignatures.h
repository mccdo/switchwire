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
#pragma once

#include <switchwire/Event.h>


#include <vector>
#include <string>

/** @file Event.h
  * This file contains a group of typedefs defining common signal types by
  * a memorable name. We use this strategy in our application code to make
  * event declarations more compact and readable.
  **/
/// @namespace switchwire
namespace switchwire
{
    ///Signal with no arguments and no returns
    typedef Event< void () > VoidSignal_type;

    ///Signal for a String
    typedef Event< void ( std::string const& ) > StringSignal_type;
    typedef Event< void ( std::string const&, std::string const& ) > TwoStringSignal_type;
    typedef Event< void ( std::string const&, std::string const&, std::string const& ) > ThreeStringSignal_type;

    ///Signal for a bool
    typedef Event< void ( bool const& ) > BoolSignal_type;

    ///Signal for double
    typedef Event< void ( double const& ) > DoubleSignal_type;
    typedef Event< void ( double const&, double const& ) > TwoDoubleSignal_type;
    typedef Event< void ( double const&, double const&, double const& ) > ThreeDoubleSignal_type;

    ///Signal for int
    typedef Event< void ( int const& ) > IntSignal_type;
    
    ///Signal for bools and vectors
    typedef Event< void ( const bool, const std::vector< double >&  ) > BoolAndDoubleVectorSignal_type;

}



