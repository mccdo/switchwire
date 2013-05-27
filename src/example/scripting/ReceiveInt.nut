function Execute()
{
    VoidIntSlotConnector <- VoidIntSlot;
    VoidIntSlotConnector.ConnectSlotToSignal( "prt", "ATestEvent" );
}

// This function is set up as a slot in the code above
function prt(n)
{
    print( "prt: " + n + "\n" );
}
