#include "process.h"
#include "processMgmt.h"
#include "processor.h"
#include "scheduler.h"

#include <chrono> // for sleep
#include <thread> // for sleep

int main(){
    ShortestJobNext knownScheduler = ShortestJobNext(Processor());
    Scheduler* myScheduler = Factory::createAlgorithm(SJN, Processor());

    knownScheduler.print();
    myScheduler->print();

    return 0;
}