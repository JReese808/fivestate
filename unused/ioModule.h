#ifndef FIVE_STATE_IO_H
#define FIVE_STATE_IO_H

#include<vector>
using namespace std;

#include "../process.h"

struct IOEvent
{
    IOEvent() :  id(9999999), time(-1), duration(0) {};
    IOEvent(const int& t, const int& d, const unsigned int& newId) : id(newId), time(t), duration(d)  {}

    unsigned int id;

    long time;       // The time the event occurs during the process execution
    long duration;   // The duration that the process will be Blocked by this IOEvent
};

struct IOInterrupt
{
    IOInterrupt() : ioEventID(99999), procID(99999) {};
    IOInterrupt(const unsigned int& eId, const unsigned int& pId) : ioEventID(eId), procID(pId) {};

    unsigned int ioEventID;
    unsigned int procID;
};

class IOModule
{
    public:
      IOModule(list<IOInterrupt>& ioIntVec) : m_intVec(ioIntVec) {}

      inline void ioProcessing(const int& curTimeStep)
      {
        for(int i = 0, i_end = m_pending.size(); i < i_end; ++i)
        {
            if(curTimeStep == m_pending[i].first)
            {
                m_intVec.push_back(m_pending[i].second);
                m_pending.erase(m_pending.begin() + i);
                --i;
                --i_end;
            }
        }
      }

      inline void submitIORequest(const int& curTimeStep, const IOEvent& ioEvent, const Process& proc)
      {
        m_pending.push_back(make_pair(curTimeStep + ioEvent.duration, IOInterrupt(ioEvent.id, proc.id)));
      }

    private:
      list<IOInterrupt>& m_intVec;
      vector<pair<int, IOInterrupt> > m_pending;
};

#endif