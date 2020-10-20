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
    volatile bool * thread_ready;
    volatile bool   thread_start;

    std::condition_variable cond;
    std::mutex mtx;
    std::unique_lock<std::mutex> * lock;

    void makeVector();

    void SendSignal(NODE *node, WIREID dest, wireclass::SIGNAL sig);
    static void * beginThread(Simulator * sim, const int * tid, volatile bool * trd);

    int Simulate();
};


/*
int SimuInit();
int SimuReset();
int Simulate();

void SendSignal(NODE * node, WIREID dest, WIRE::SIGNAL sig);
//void SendInteger(SENDFORM sendform, DEFT_WORD integer);

int SimuReSizeList(DEFT_ADDR size);

void makeVector();
static int setThread(int);


// definition(functions)
// =static
// =public
*/


#endif
