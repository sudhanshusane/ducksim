#include <iostreams>
#include <vector>
#include "flit.h"

/**
 * The TEST namespace exists to facilitate consistent class testing nomenclature.
 * The proper way to test a class is to call the class name without parameters,
 * making sure to specify it in the TEST namespace.
 *
 * For example:
 *
 *   bool isWorking = TEST::Flit();
 *
 */
namespace TEST {

  public bool Flit() {
    bool result;
    std::Vector<int> v;
    DuckSim::Flit f;

    v.push_down(1);
    f = new DuckSim::Flit(v, 1);
    result = true; //TODO: Actually test Flit stuff out.
    delete f;
    
    return result;
  } //end: TEST::Flit
  
} //end: TEST (namespace)

