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



namespace switchwire
{
/// @file BooleanPropagationCombiner.h
/// @namespace switchwire
/// @class BooleanPropagationCombiner
/// Custom combiner for signals that accept a boolean return value. Propagation
/// of the signal stops when a slot returns @c true. This can be used to
/// set up hierachichal chains of slots in which one slot can sink the signal
/// so that all slots below it in the hierarchy don't get called.
struct SWITCHWIRE_EXPORT BooleanPropagationCombiner {
typedef bool result_type; // This typedef is req'd by boost::signals2 combiner
                          // interface.

template<typename InputIterator>
result_type operator()(InputIterator first, InputIterator last) const
{
    while (first != last)
    {
        if (result_type sinkEvent = *first)
        {
            return sinkEvent;
        }

        ++first;
    }
    return false;
}
};

} // namespace switchwire
