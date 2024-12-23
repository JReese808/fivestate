#include "process.h"
#include "processMgmt.h"
#include "processor.h"
#include "scheduler.h"

#include <chrono> // for sleep
#include <thread> // for sleep


// Main function
int main(){

    cout << "started" << endl;
    //creating processMgmt object with chosen scheduler
    Alg algorithmChoice = RR;
    ProcessManagement processMgmt = ProcessManagement(Factory::createAlgorithm(algorithmChoice, Processor()));
    processMgmt.printScheduler();

    cout << "declaring variables" << endl;
    long time = 0;
    long sleepDuration = 0;
    string file = "./procListNoIo.txt";
    stringstream ss;

    //filling all processes
    cout << "reading process file" << endl;
    processMgmt.readProcessFile(file);
    cout << "reading complete" << endl;
    processMgmt.printAllProcesses();
    int processesRemaining = processMgmt.numProcesses();

    cout << "Starting loop \n" << endl;
    //keep running the loop until all processes have been added and have run to completion
    while(processesRemaining > 0){
        // cout << "iteration" << endl;
        //Update our current time step
        ++time;
        //let new processes in if there are any
        // cout << "activating processes" << endl;
        processMgmt.activateProcesses(time);
        //run a step
        // cout << "running step" << endl;
        stepActionEnum stepAction = processMgmt.runStep(time);
        if(stepAction == complete){
            processesRemaining--;
        }

        // cout << "starting display" << endl;
        // All terminal visuals
        cout << setw(5) << time << "\t"; 
        switch(stepAction){
            case admitNewProc:
                cout << "[  admit]\t";
                break;
            case handleInterrupt:
                cout << "[ inrtpt]\t";
                break;
            case beginRun:
                cout << "[  begin]\t";
                break;
            case continueRun:
                cout << "[contRun]\t";
                break;
            case contextSwitch:
                cout << "[  switch]\t";
                break;
            case complete:
                cout << "[ finish]\t";
                break;
            case noAct:
                cout << "[*noAct*]\t";
                break;
        }
        // cout << "printing states" << endl;
        processMgmt.printStates();
        // processMgmt.printScheduler();

        // Sleep
        // cout << "sleeping" << endl;
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));
    }
    cout << "loop complete" << endl;
    processMgmt.printAllProcesses();
    return 0;
}
