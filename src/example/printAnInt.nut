// We've bound a C++ class that creates, registers, and exposes a void(int)
// signal. The class is bound to the name "SetupVoidIntSignal".
// We use this class to setup a signal registered as ScriptIntSignal and bound
// to the Squirrel name MyScriptIntSignal.
VoidIntMaker <- SetupVoidIntSignal;
VoidIntMaker.RegisterSignal( "ScriptIntSignal", "MyScriptIntSignal" );

// We could set up more signals of void(int) type using the same VoidIntMaker
// class, like this:
// VoidIntMaker.RegisterSignal( "AnotherScriptIntSignal", "MySecondIntSignal" );

print( "Squirrel script is about to call ScriptIntSignal with argument 8675309...\n" );
MyScriptIntSignal.signal( 8675309 );

// This function is set up as a slot
function prt(n)
{
    // Just print out the number we were passed
    print( "Script prt: argument = " + n + "\n" );

    // Since we've bound a std::vector<int> to the classname IntVec, we can
    // construct and use one like this:
    iv <- IntVec();
    iv.push_back( 123 );
    iv.push_back( 456 );
    iv.push_back( 789 );

    for( local i = 0; i < iv.size(); ++i )
    {
        print( iv.at( i ) + "\n" );
    }

    mii <- IntStringMap();
    mii.add( 1, "Zanzibar" );
    mii.add( 2, "La Jolla" );
    print( "\n" + mii.find( 2 ) + "\n" );
    print( mii.find( 1 ) + "\n" );
    print( mii.find( 3 ) + "\n" );

    // Now we're going to fire the signal that has been exposed with the name
    // THEstringSignal
    str <- "Scripted string";
    ::THEstringSignal.signal( "Scripted string" );
}

// This function is set up as a slot
function prtStr( str )
{
    print( "Script prtStr: " + str + "\n" );
}

