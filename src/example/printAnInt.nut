// We've bound a C++ function called SetupSignal that can create, register, and expose
// a void(int) signal with name ScriptIntSignal, bound here to the name MyScriptIntSignal.
// Set one up, then fire it.
SetupSignal( "ScriptIntSignal", "MyScriptIntSignal" );
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

