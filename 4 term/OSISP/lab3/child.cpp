#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ncurses.h>

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct sigaction printSignal, closeSignal, alarmSignal;
bool Print = false;
bool EndAlarm = false;
bool Close = false;
char parentPID[256];
int result = 0;

struct TimerStat
{
    int first;
    int second;

}timeStat;

struct Stat
{
    int res00 = 0;
    int res01 = 0;
    int res10 = 0;
    int res11 = 0; 
}all_stat;

void setPrint(int sign)
{
    Print = true;
}

void setClose(int sign)
{
    Close = true;
}

void setAlarm (int sign)
{     
    EndAlarm = true;
    if(timeStat.first == timeStat.second)
    {
        if(timeStat.first == 1){
            all_stat.res11++;
        }
        else{
            all_stat.res00++;
        }
    }
    else{
        if(timeStat.first ==0){
            all_stat.res01++;
        }
        else{
            all_stat.res10++;
        }
    }
    
}

void initSignalHandlers()
{
    printSignal.sa_handler = setPrint;
    sigaction(SIGUSR1, &printSignal, NULL);

    closeSignal.sa_handler = setClose;
    sigaction(SIGUSR2, &closeSignal, NULL);

    alarmSignal.sa_handler = setAlarm;
    sigaction(SIGALRM, &alarmSignal, NULL);
}

int main(int argc, char* argv[])
{

    printf("New child process pid: %d, ppid: %d  \n", getpid(), getppid());
    initSignalHandlers();

    char buf[256];
    int count = 100;
    while (count --)
    {
        bool fl;
        EndAlarm = false;
        ualarm(10000, 0);
        while(!EndAlarm)
        {
            timeStat.first = fl ? 1:0;
            timeStat.second = fl ? 1:0;
            fl = fl ? false : true;
        }
    }

    sprintf(buf, " Child%d 00: %d 01:%d, 10:%d, 11:%d", atoi(argv[0]), all_stat.res00, all_stat.res01, all_stat.res10, all_stat.res11);

    while (true)
    {
        if (Print)
        {
            usleep(10000);
            Print = false;                
            cout << buf << endl;
            napms(300);
            
            kill(getppid(), SIGUSR1);
        }
        
        if (Close)
        {
            break;
        }
    }


    return 0;
}