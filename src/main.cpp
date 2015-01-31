#include <iostream>
#include <exception>
#include "main.h"
#include "globals.h"

int main( int argc, char * argv[] ) {
  int result = 0;
  try {

    /* NOTE:
     *
     * Because we are not in a namespace now, components of the simulator should
     * be identified using their fully qualified name, for example:
     *
     *   DuckSim::Flit f = new DuckSim::Flit(...);
     *
     * Once control has been passed into the namespace, objects can be referred
     * to without the qualifier, like:
     *
     *   Flit f = new Flit(...);
     *
     */
    
    //TODO: Parse command line arguments
    //TODO: Initialize Global Variable classes
    //TODO: Initialize Application
    //TODO: Initialize Logging / Introspection (threads?)
    //TODO: Connect Objects / Callbacks
    //      (would be nice to have the ability to real-time monitor w/curses display)
    //TODO: Pass control off to Application
  }
  catch( const Exception& ex ) {
    printf( "An exception has occured in the main() function: %s", ex.what() );
  }

  return result;
} //end: main
