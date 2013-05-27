function Execute()
{
// In the c++ application, we've bound an existing C++ signal to the name
// "ExplicitIntSignal"
    ::ExplicitIntSignal.signal( 1 );
    ::ExplicitIntSignal.signal( 2 );
    ::ExplicitIntSignal.signal( 3 );
    ::ExplicitIntSignal.signal( 4 );
}
