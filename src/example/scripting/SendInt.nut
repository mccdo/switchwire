function Execute()
{
// We've bound a C++ class that creates, registers, and exposes a void(int)
// signal. The class is bound to the name "IntSignal". We use this
// class to setup a signal registered as ScriptIntSignal and bound to the
// Squirrel name MyScriptIntSignal.
    VoidIntMaker <- IntSignal;
    VoidIntMaker.RegisterSignal( "ScriptIntSignal", "MyScriptIntSignal" );

// We could set up more signals of void(int) type using the same VoidIntMaker
// class, like this:
// VoidIntMaker.RegisterSignal( "AnotherScriptIntSignal", "MySecondIntSignal" );

    MyScriptIntSignal.signal( 1 );
    MyScriptIntSignal.signal( 2 );
    MyScriptIntSignal.signal( 3 );
    MyScriptIntSignal.signal( 4 );
}
