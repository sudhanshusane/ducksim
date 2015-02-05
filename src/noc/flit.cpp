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

  /** Construct a new flit. */
  Flit::Flit( std::vector<int> data, int timeStampGenerated ) {
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
  Flit::~Flit() {
    return;
  } // end:~Flit (destructor)

  /**
   * Increases the hop count of the flit after it traverses a physical link.
   *
   */
  void Flit::increaseHop() {
    hop++;
    return;
  } //end: increaseHop

  /**
   * Returns a count of hops that this flit has traversed.
   *
   * @return the hop count
   */
  virtual int Flit::getHopCount() {
    return hop;
  } //end: getHopCount

  /**
   * Returns the type of the flit. 
   *
   * @return one bit information to distinguish HEADER or DATA flit
   */
  virtual int Flit::getType() {
    return this.data[0] & ((1 << globals.NUM_FLIT_TYPE_BITS) - 1);
  } //end: getType

  /**
   * Returns the virtual channel information of the flit.
   *
   * @return virtual channel number
   */
  virtual int Flit::getVirtualChannelNo() {
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
  virtual int Flit::getAddressLength() {
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
  virtual int Flit::getPacketLength() {
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


  /**
   * Returns the address of the source node.  While doing so, it decodes
   * the flit data to retrieve the sought information.  As the address might
   * overlap in two adjacent 32-bit data, it takes care of such situation.
   *
   * @return address of the source node.
   */
  virtual int Flit::getSourceNode() {
    int temp;
    int addrSize = getAddressLength();
    int noOfBit = globals.NUM_FLIT_TYPE_BITS + globals.NUM_VCID_BITS
      + globals.NUM_ADDR_BITS + globals.NUM_FLITS_BITS;
    int noOfInt = noOfBit / globals.INT_SIZE;
    int rest = globals.INT_SIZE - (noOfBit % globals.INT_SIZE);

    if (rest >= addrSize) {
      temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
	& ((1 << addrSize) - 1);
    } else {
      temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
	& ((1 << rest) - 1);
      temp = ((data[noOfInt + 1] & ((1 << (addrSize - rest)) - 1)) << rest)
	| temp;
    }
    
    return temp;
  } //end: getSourceNode

  /**
   * Returns the address of the destination node. While doing so, it decodes
   * the flit data to retrieve the sought information. As the address might
   * overlap in two adjacent 32 bit data, it takes care of such situation.
   * 
   * @return address of the destination node.
   */
  virtual int Flit::getDestinationNode() {
    int temp;
    int addrSize = getAddressLength();
    int noOfBit = globals.NUM_FLIT_TYPE_BITS + globals.NUM_VCID_BITS
                  + globals.NUM_ADDR_BITS + globals.NUM_FLITS_BITS
                  + addrSize;
    int noOfInt = noOfBit / globals.INT_SIZE;
    int rest = globals.INT_SIZE - (noOfBit % globals.INT_SIZE);
    
    if (rest >= addrSize) {
      temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
              & ((1 << addrSize) - 1);
    } else {
      temp = (data[noOfInt] >>> (globals.INT_SIZE - rest))
              & ((1 << rest) - 1);
      temp = ((data[noOfInt + 1] & ((1 << (addrSize - rest)) - 1)) << rest)
              | temp;
    }
    
    return temp;
  } //end:getDestinationNode

  
  /**
   * Returns the data of the flit
   *
   * @return an integer vector of data of the flit.
   */
  virtual std::vector<int> Flit::getData() {
    std::vector<int> temp( data.length );
    for (int i = 0; i < data.length; i++) {
      temp[i] = data[i];
    }
    temp[0] >>>= (globals.NUM_FLIT_TYPE_BITS + globals.NUM_VCID_BITS);

    return temp;
  } //end: getData


  /**
   * Return the Hex value of the flit data.
   * This is the equivalent of Java's .toString() routine for stream-contexts.
   */
  virtual std::ostream& Flit::operator<<(std::ostream &strm, const Flit &f) {
    return strm << getHexData();
  } //end: << (output stream operator override)

  /**
   * Return the Hex value of the flit data.
   * An accessory function that can be called in non-stream contexts.
   *
   */
  virtual std::string Flit::getHexData() {
    std::string temp = "";
    for (int i = 0; i < data.length; i++) {
      temp += std::hex << data[i];
    }
    return temp;
  } //end: getHexData


  /**
   * Sets the virtual channel information of the flit datya
   *
   * @param vcID virtual channel number
   *
   */
  virtual void Flit::setVirtualChannelNo(int vcID) {
    int mask = (1 << globals.NUM_VCID_BITS) - 1;
    mask <<= globals.NUM_FLIT_TYPE_BITS;
    mask = ~mask;
    data[0] &= mask;
    data[0] |= (vcID << globals.NUM_FLIT_TYPE_BITS);
  } //end: setVirtualChannelNo

  /**
   * Sets the last service time information by the specified time stamp.
   *
   * @param timeStamp
   *        the time stamp (cycle) when the flit receives some service.
   *
   */
  virtual void Flit::setTimeStampLastService(int timeStamp) {
    this->timeStampLastService = timeStamp;
  } //end: setTimeStampLastService

  /**
   * Sets the generation time stamp.
   *
   * @param timeStamp
   *        the time information when the flit is generated.
   *
   */
  virtual void Flit::setTimeStampGenerated(int timeStamp) {
    this->timeStampGenerated = timeStamp;
  } //end: setTimeStampGenerated

  /**
   * Returns the generation time stamp of the flit
   *
   * @return generation time of the flit.
   *
   */
  virtual int Flit::getTimeStampGenerated() {
    return this->timeStampGenerated;
  } //end: getTimeStampGenerated


  /**
   * Return the source address of the flit.
   *
   * @return address of the source node.
   *
   */
  virtual int Flit::getSource() {
    return src;
  } //end: getSource


  /**
   * Return the destination address of the flit.
   *
   * @return address of the destination node.
   *
   */
  virtual int Flit::getDest() {
    return dest;
  } //end: getDest


  /**
   * Sets the source address of the flit.
   *
   * @param src
   *        address of the source node
   */
  virtual void Flit::setSource(int src) {
    this->src = src;
    return;
  } //end: setSource


  /**
   * Sets the destination address of the flit
   *
   * @param dest
   *        address of the destination node
   */
  virtual void Flit::setDest(int dest) {
    this->dest = dest;
    return;
  } //end: setDest

} //end: DuckSim (namespace)
