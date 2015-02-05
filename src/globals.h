#ifndef DUCKSIM_GLOBALS_H
#define DUCKSIM_GLOBALS_H

namespace DuckSim {

  /** Note that all public data members need to be constant values! */
  class Globals {
  private:
    void getLock(int domain);
    void releaseLock();
  public:
    Globals();
    ~Globals();


    // The CONSTANTS section: ...
    // TODO: This needs to get cleaned up, perhaps nested in a class-name substructure?
    
    const int NUM_FLIT_TYPE_BITS = 1;
    const int NUM_VCID_BITS = 2;
    const int INT_SIZE = sizeof(int);
    const int NUMBER_OF_IP_NODE = 4;



    
  }; //end: Globals (class)
} //end: DuckSim (namespace)

#endif
