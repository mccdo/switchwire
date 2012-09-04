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

#if defined(_MSC_VER)
#pragma warning( disable : 4503 )
#pragma warning( disable : 4251 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( SWITCHWIRE_LIBRARY_STATIC )
    #    define SWITCHWIRE_EXPORT
    #    define SWITCHWIRE_LOCAL
    #  elif defined( SWITCHWIRE_LIBRARY )
    #    define SWITCHWIRE_EXPORT   __declspec(dllexport)
    #    define SWITCHWIRE_LOCAL
    #  else
    #    define SWITCHWIRE_EXPORT   __declspec(dllimport)
    #    define SWITCHWIRE_LOCAL
    #  endif
#else
  #if __GNUC__ >= 4
    # if defined( SWITCHWIRE_LIBRARY_STATIC )
    #    define SWITCHWIRE_EXPORT
    #    define SWITCHWIRE_LOCAL
    # else
    #    define SWITCHWIRE_EXPORT   __attribute__ ((visibility ("default")))
    #    define SWITCHWIRE_LOCAL   __attribute__ ((visibility ("hidden")))
    # endif
  #else
    #  define SWITCHWIRE_EXPORT
    #  define SWITCHWIRE_LOCAL
  #endif
#endif
