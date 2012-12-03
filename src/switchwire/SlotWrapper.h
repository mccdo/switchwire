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

#include <switchwire/SlotWrapperBase.h>
#include <stdio.h>


namespace switchwire
{
/// @file SlotWrapper.h
/// @namespace switchwire
/** @class SlotWrapper
 * SlotWrapper provides a wrapper around a slot, allowing slots with different
 * types (signatures) to be passed into the same function and to be held in
 * containers (via SignalWrapperBase). If you use the functions in
 * ConnectSignals.h to make connections between signals and slots (and we
 * highly reccommend this practice) you will never need to explicitly use
 * this class.
 *
 * SlotWrapper holds a reference to a boost::signals2::signal<T>::slot_type.
 **/
template <typename T>
class SlotWrapper : public SlotWrapperBase
{
public:

    /**
     * Constructs a SlotWrapper.
     * Notice that the template parameter and the type
     * passed in to the constructor differ slightly: the template parameter should
     * be a boost::signals2::signal<> type, whereas the argument to the constructor
     * is a boost::signals2::signal<>::slot_type&.
     *
     * For a usage example, please
     * see EventManager::ConnectSignal, and pay attention to the template
     * parameter when instantiating the wrapper.
     * @param slot A reference to the slot.
     * 
     * @see EventManager::ConnectSignal
     **/
    //SlotWrapper( const typename T::slot_type& slot ) :
    SlotWrapper( const typename T::slot_type* slot ) :
    mSlot( slot )
    {
        ;
    }

    SlotWrapper( const SlotWrapper& orig )
    {
        mSlot = orig.mSlot;
    }

    SlotWrapper& operator= (const SlotWrapper& orig)
    {
        mSlot = orig.mSlot;
        return *this;
    }

    virtual ~SlotWrapper( )
    {
        delete mSlot;
    }

    const typename T::slot_type& GetSlot( )
    {
        return (*mSlot);
    }
private:
    //const typename T::slot_type& mSlot;
    const typename T::slot_type* mSlot;

};
/*
Test class to try and make a smart pointer for the SlotWrapper
templated class.
template <class T> 
class SlotWrapperTPtr : boost::shared_ptr< SlotWrapper< T > >
{
public:
    SlotWrapperTPtr( const typename T::slot_type* slot ) 
        :
        SlotWrapper( slot )
    {
        ;
    }

    SlotWrapperTPtr( const SlotWrapperTPtr& orig )
        :
        SlotWrapper( orig )
    {
        ;
    }
};
*/
}

