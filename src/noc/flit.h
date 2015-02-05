#ifndef DUCKSIM_NOC_FLIT_H
#define DUCKSIM_NOC_FLIT_H

namespace DuckSim {
  class Flit {

  private:
    /** Provide an override for the << operator, in case this object
     * is (for some reason) used in a stream context, no we can output
     * some string value of the flit. */
    friend std::ostream& Flit::operator<<(std::ostream&, const Flit&);

    /** Vector of data in this Flit, the default data is a single int. */
    virtual std::Vector<int> data();

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
    virtual std::vector<int> VCs(globals.NUMBER_OF_IP_NODE);

  public:
    Flit( std::vector<int> data, int timeStampGenerated );
    ~Flit();
    void increaseHop();
    virtual int getHopCount();
    virtual int getType();
    virtual int getVirtualChannelNo();
    virtual int getAddressLength();
    virtual int getPacketLength();
    virtual int getSourceNode();
    virtual int getDestinationNode();
    virtual std::Vector<int> getData();
    virtual std::ostream& Flit::operator<<(std::ostream& strm, const Flit& f);
    virtual std::string getHexData();
    virtual void setVirtualChannelNo(int vcID);
    virtual void setTimeStampLastService(int timeStamp);
    virtual void setTimeStampGenerated(int timeStamp);
    virtual int getTimeStampGenerated();
    virtual int getSource();
    virtual int getDest();
    virtual void setSource(int src);
    virtual void setDest(int dest);
    
  }; //end: Flit (class)
} //end: DuckSim (namespace)

#endif
