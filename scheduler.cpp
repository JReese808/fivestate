#include "scheduler.h"

// Allows processMgmt to fill the new_processes list
void Scheduler::addNewArrival(Process* p){
    new_processes.push_back(p);
    p->state = newArrival;
}

// Adds and sorts a process into the ready queue
void Scheduler::addNewProcess(){
    // cout << "FIFO adding new process" << endl;
    m_processes.push_back(new_processes.front());
    new_processes.front()->state = ready;
    new_processes.front() = nullptr;
    new_processes.pop_front();
}

void Scheduler::beginNewProcess(){
    m_processor.newProcess(m_processes.front());
    m_processes.front()->state = processing;
    m_processes.front() = nullptr;
    m_processes.pop_front();
    preempt = 0;
}

// Decides what happens at each time interval. Returns step action documenting what happened.
stepActionEnum Scheduler::runProcesses(const long& time){
    // cout << "scheduler layer started" << endl;
    if(new_processes.size() > 0){
        // cout << "admit new process" << endl;
        addNewProcess();
        return admitNewProc;
    } else if(m_processor.isFree()){
        // cout << "processor is free" << endl;
        if(m_processes.size() != 0){
            // cout << "beginning a run" << endl;
            beginNewProcess();
            return beginRun;
        } else {
            // cout << "no action" << endl;
            return noAct;
        }

    } else {
        // cout << "processor not free" << endl;
        bool processCompleted = m_processor.runProcess(time);
        if(processCompleted){
            return complete;
        } else {
            return continueProcessing();
        }
    }
}

void Scheduler::printReadyProcesses(){
    for(const auto& proc : m_processes){
        cout << proc->id << " ";
    }
    cout << endl;
}