#include <iostream>
#include <vector>

#include "flit.h"
#include "../globals.h"

namespace DuckSim {

  /**
   * A message (a packet) is the summation of some flits. Flit object simply
   * contains encoded data as member variable. The data is divided into different
   * fields. Both header and data flit contain flit type (1 bit) and virtual
   * channel number used. For data flit the remaining bits of the data block is
   * simply raw data taken from the message (packet). For header flit contains
   * number bit used to represent the source and destination nodes, number of
   * flits, source address and destination address sequentially.
   * 
   * @version 0.1
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
    virtual std::Vector<int> VCs(globals.NUMBER_OF_IP_NODE);

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
     * @return the hop count
     */
    virtual int getHopCount() {
      return hop;
    } //end: getHopCount

    /**
     * Returns the type of the flit. 
     *
     * @return one bit information to distinguish HEADER or DATA flit
     */
    virtual int getType() {
      return this.data[0] & ((1 << globals.NUM_FLIT_TYPE_BITS) - 1);
    } //end: getType

    /**
     * Returns the virtual channel information of the flit.
     *
     * @return virtual channel number
     */
    virtual int getVirtualChannelNo() {
      if (null == data) {
	return -1;
      }
      return (data[0] >> globals.NUM_FLIT_TYPE_BITS)
	& ((1 << globals.NUM_VCID_BITS) - 1);
    } //end: getVirtualChannelNo

    /**
     * Returns the number of bits required to encode and address in the flit
     *
     * @return number of bits to encode an address
     */
    virtual int getAddressLength() {
      int temp;
      int noOfBit = globals.NUM_FLIT_TYPE_BITS + globals.NUM_VCID_BITS;
      int noOfInt = noOfBit / globals.INT_SIZE;
      int rest = globals.INT_SIZE - (noOfBit % globals.INT_SIZE);

      if (rest >= globals.NUM_ADDR_BITS) {
	temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
	  & ((1 << globals.NUM_ADDR_BITS) - 1);
      } else {
	temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
	  & ((1 << rest) - 1);
	temp = ((data[noOfInt + 1] & ((1 << (globals.NUM_ADDR_BITS - rest)) - 1)) << rest)
	  | temp;
      }

      return temp;
    } //end: getAddressLength

    /**
     * Returns the number of flits in the packet to which this flit belongs.
     *
     * @return packet length in flits
     */
    virtual int getPacketLength() {
      int temp;
      int noOfBit = globals.NUM_FLIT_TYPE_BITS + globals.NUM_VCID_BITS
	+ globals.NUM_ADDR_BITS;
      int noOfInt = noOfBit / globals.INT_SIZE;
      int rest = globals.INT_SIZE - (noOfBit % globals.INT_SIZE);

      if (rest >= globals.NUM_FLITS_BITS) {
	temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
	  & ((1 << globals.NUM_FLITS_BITS) - 1);
      } else {
	temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
	  & ((1 << rest) - 1);
	temp = ((data[noOfInt + 1] & ((1 << (globals.NUM_FLITS_BITS - rest)) - 1)) << rest)
	  | temp;
      }

      return temp;
    } //end: getPacketLength


    
  } //end: Flit (class)
} //end: DuckSim (namespace)
