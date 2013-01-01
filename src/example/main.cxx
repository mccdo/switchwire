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
// This block of includes is only required if you intend to use EventManager's
// logging facilities.
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/SimpleFileChannel.h>

// The minimal set of headers required to register a signal and connect a slot
// to it.
#include <switchwire/ConnectSignals.h>
#include <switchwire/Event.h>

// If you're just registering a signal but not connecting any slots in that
// compilation unit, you only need <switchwire/EventManager.h>

void prt( int num )
{
    std::cout << "prt: argument = " << num << std::endl;
}

int main()
{
    // Set up a logger so we can see log messages from the Eventmanager library.
    // This is not required in a program using this library, but it can be very
    // useful for debugging event/slot connections during development. Here we
    // set the log level to "information". For more thorough debugging,
    // recompile switchwire library with SWITCHWIRE_DEBUG defined, and set
    // the log level to either "debug" or "trace".
    Poco::Logger::root().setLevel("information");
    Poco::ConsoleChannel* console = new Poco::ConsoleChannel;
    Poco::PatternFormatter* formatter = new Poco::PatternFormatter;
    formatter->setProperty("pattern", "%s: %t");
    Poco::FormattingChannel* formattingChannel =
            new Poco::FormattingChannel( formatter, console );
    Poco::Logger::root().setChannel( formattingChannel );

    // Now we're going to set up a file channel for logging all signal registrations.
    // This technique can be used to dump out a list of all signal names that are
    // registered during an entire run of an application.
    Poco::SimpleFileChannel* fileChannel = new Poco::SimpleFileChannel( "Signals.txt" );
    Poco::Logger::get( "RegLog" ).setChannel( fileChannel );
    switchwire::EventManager::instance()->LogAllRegistrations( Poco::Logger::get( "RegLog" ) );


    // With logging mechanisms out of the way, let's get started on real code:

    std::cout << std::endl << "Log messages are prefixed with 'switchwire::EventManager'" << std::endl << std::endl;


    // Declare an event (usually done as a class member variable)
    switchwire::Event< void (int) > intSignal;

    // This "useless signal" demonstrates registering the same signal with
    // two different names, and shows that when fired, a log entry is made for
    // each name.
    switchwire::Event< bool (float, double, int, const std::string& ) > uselessSignal;
    switchwire::EventManager::instance()->RegisterSignal( &uselessSignal, "UselessSignal" );
    switchwire::EventManager::instance()->RegisterSignal( &uselessSignal, "TheSameUselessSignalWithADifferentName" );
    uselessSignal.EnableNotification( "UselessSignal" );
    uselessSignal.EnableNotification( "TheSameUselessSignalWithADifferentName" );
    uselessSignal.signal( 1.2f, 1.3, 7, "A Duck!" );
         
    // Create a ScopedConnectionList, which is required for connecting to an
    // event. This is frequently a class member variable also.
    switchwire::ScopedConnectionList connections;
         
    // Request a connection between "ATestEvent" and function prt. This shows
    // how to connect to static functions or other functions which are not
    // members of a class. Notice the word "Static" in the function name.
    switchwire::ConnectSignalsStatic<void (int)>(
                    "ATestEvent",
                    &prt,
                    connections/*,
                    switchwire::EventManager::any_SignalType,
                    switchwire::EventManager::normal_Priority*/ );

    // Register the event with EventManager
    switchwire::EventManager::instance()->
      RegisterSignal( &intSignal , "ATestEvent" );

    // Notice that we don't call EnableNotification for intSignal, so it doesn't
    // get logged.

    // Print out a list of all signals that have been registered
    std::cout << "\nList of registered signals:" << std::endl;
    std::vector< std::string > names = switchwire::EventManager::instance()->GetAllSignalNames();
    for( size_t index = 0; index < names.size(); ++index )
    {
        std::cout << "\t" << names.at( index ) << std::endl;
    }
    std::cout << std::endl;
                            
    // Fire the signal several times
    intSignal.signal( 1 );
    intSignal.signal( 0 );
    intSignal.signal( 5 );
    intSignal.signal( 4 );
    intSignal.signal( 5 );

    // The next two lines are not generally necessary, but demonstrate how to
    // properly trigger memory cleanup when you have slots in a dynamic plugin.
    connections.Reset();
    switchwire::EventManager::instance()->CleanupSlotMemory();

#if 0
    // Expired event test
    {
        switchwire::Event< void (int) > intSignal2;
        switchwire::EventManager::instance()->
                RegisterSignal( &intSignal2 , "ExpiredSignal" );
    }
    // intSignal2 has now gone out of scope, so we should fail to connect
    // and the event should be scrubbed from EventManager's lists. Info
    // will show up in the log. This also demonstrates the optional macro
    // version of connecting to an event, which is useful if you really dislike
    // templates. Use of the macro is not critical to the example of expired
    // signals, however.
#include <switchwire/OptionalMacros.h>
    CONNECTSIGNAL_STATIC( "ExpiredSignal",
                            void( int ),
                            &prt,
                            connections,
                            normal_Priority );
#endif


    delete formatter;

    return 0;
}
