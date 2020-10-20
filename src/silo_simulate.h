#ifndef SILO_SIMULATE_HEAD
#define SILO_SIMULATE_HEAD

#include "silo_define.h"

#include "silo_node.h"

#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

typedef class simulatorclass Simulator;

class simulatorclass {
public:
    simulatorclass();
    ~simulatorclass();

    std::vector<NODE *> * NextExecVector;
    char * SentList;
    int numberOfthread;

    int  * thread_id;
    bool * thread_ready;
    bool * thread_start;

    std::condition_variable condsub, condmain;
    std::mutex mtxsub, mtxmain;
    std::unique_lock<std::mutex> * locksub, * lockmain;
	
	
	
    void SendSignal(NODE *node);
    static void * Thread(Simulator * sim, const int * tid, volatile bool * trd);

    int begin();
    int beginTicks(DEFT_DWRD);
    int beginCycle(DEFT_DWRD);
    void makeVector();

private:
	NODEID Simulation(const int * tid);
};





#endif
