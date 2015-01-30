#include <iostream>
#include <vector>

#include "flit.h"
#include "instance.h"

/**
 * A message (a packet) is the summation of some flits. Flit object simply
 * contains encoded data as member variable. The data is divided into different
 * fields. Both header and data flit contain flit type (1 bit) and virtual
 * channel number used. For data flit the remaining bits of the data block is
 * simply raw data taken from the message (packet). For header flit contains
 * number bit used to represent the source and destination nodes, number of
 * flits, source address and destination address sequentially.
 * 
 * @version 1.0
 * 
 */

class Flit {

private:
  /** Vector of data in this Flit, the default data is a single int. */
  virtual std::Vector<int> data(1);

  /** The time stamp or simulation cycle when the flit was generated. */
  virtual int timeStampGenerated;

  /** The time stamp or simulation cycle when the flit was last served. */
  virtual int timeStampLastService;

  /** The address of the source node. */
  virtual int src;

  /** The address of the destination node. */
  virtual int dest;

  /** The number of physical links (hops) this flit has traversed. */
  virtual int hop;

  /** A vector of virtual channels.
   * TODO: Explain how these are used here.
   */
  virtual std::Vector<int> VCs(instance.NUMBER_OF_IP_NODE);

public:

  /** Construct a new flit. */
  Flit( std::Vector<int> data, int timeStampGenerated ) {
    this->data = data;
    this->timeStampGenerated = timeStampGenerated;
    this->timeStampLastService = timeStampGenerated;
    this->hop = 0;

    /**  Initialize our VCs as all unused. */
    for (auto& vc : VCs)
      vc = -1;

    return;
  } // end:Flit (constructor)

  /** Discard this flit. */
  ~Flit() {
    return;
  } // end:~Flit (destructor)

  /**
   * Increases the hop count of the flit after it traverses a physical link.
   *
   */
  void increaseHop() {
    hop++;
    return;
  } //end: increaseHop

  /**
   * Returns a count of hops that this flit has traversed.
   *
   */
  virtual int getHopCount() {
    return hop;
  } //end: getHopCount

  /**
   * 



}
