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


#include<boost/signals2/signal.hpp>


namespace switchwire
{
/// @file SlotWrapperBase.h
/// @namespace switchwire
/** @class SlotWrapperBae
  * Base class for templated SlotWrapper.
  * Existence of a base class allows disparate instances of SlotWrapper<> to be
  * passed into the same function without requiring multiple overloaded variations,
  * and also allows disparate instance of SlotWrapper<> to be held in a single
  * container.
**/
class SlotWrapperBase
{
public:
    SlotWrapperBase( ){}
    virtual ~SlotWrapperBase( ){}
private:

};

}
