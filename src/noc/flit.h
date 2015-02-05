#ifndef DUCKSIM_NOC_FLIT_H
#define DUCKSIM_NOC_FLIT_H

namespace DuckSim {
  class Flit {

  private:
    friend std::ostream& operator<<(std::ostream&, const Flit&);
    virtual std::Vector<int> data(1);
    virtual int timeStampGenerated;
    virtual int timeStampLastService;
    virtual int src;
    virtual int dest;
    virtual int hop;
    virtual std::Vector<int> VCs(globals.NUMBER_OF_IP_NODE);

  public:
    Flit( std::Vector<int> data, int timeStampGenerated );
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
    virtual std::ostream& operator<<(std::ostream &strm, const Flit &f);
    virtual std::string getHexData();
    virtual void setVirtualChannelNo(int vcID);
    virtual void setTimeStampLastService(int timeStamp);
    virtual void setTimeStampGenerated(int timeStamp);
    virtual int getTimeStampGenerated();
    virtual int getSource();
    virtual int getDest();
    virtual void setSource(int src);
    virtual void setDest(int dest);
    
  } //end: Flit (class)
} //end: DuckSim (namespace)

#endif
