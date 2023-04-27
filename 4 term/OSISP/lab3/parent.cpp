#define MAX_AMOUNT_OF_PROCESSES 5

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <ncurses.h>
#include<sys/select.h>
#include<curses.h>

#include <vector>
#include <iostream>

using namespace std;

vector<pid_t> procInfo;
struct sigaction printSignal; 
bool Print = true;
bool printAvailable[] = {true, true, true, true, true};
char parentPID[256];
int i = 0;

int myGetch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void setPrint(int sig)
{
    if (procInfo.size())
    {
        if (++i >= procInfo.size())
        {
            i = 0;
        }
        int j = 0;
        while(printAvailable[i] != true)
        {
            if (++i >= procInfo.size())
            {
                i = 0;
            }
            j++;
            if(j == MAX_AMOUNT_OF_PROCESSES){
                Print = false;
                break;}
        }
        napms(150);
        if(Print == true)
            kill(procInfo[i], SIGUSR1);
    }
    else
    {
        Print = true;
    }
}

void initSignalHandlers()
{
    printSignal.sa_handler = setPrint;
    printSignal.sa_flags =  SA_RESTART;
    sigaction(SIGUSR1, &printSignal, NULL);
}

void addOneProcess() {
    procInfo.push_back(fork());

    if (procInfo.back() == 0)
    {
        char instanceID[10];
        sprintf(instanceID, "%ld", procInfo.size());
        if (execlp("./child", instanceID, parentPID, NULL) == -1)
        {
            procInfo.pop_back();
            cout << "Error." << endl;
        }
    }
}

void removeOneProcess()
{
    kill(procInfo.back(), SIGUSR2);
    waitpid(procInfo.back(), NULL, 0);

    printf("Process %d was deleted \n", procInfo.back());

    procInfo.pop_back();

    printf("%ld left", procInfo.size());
}

void showOptionList()
{
    cout << "'+' to create new child;" << endl;
    cout << "'-' to delete last child;" << endl;
    cout << "'l' to show all active processes;" << endl;
    cout << "'k' to delete all childs;" << endl;
    cout << "'s' to disable displaying statistics;" << endl;
    cout << "'g' to allow displaying statistics;" << endl;
    cout << "'p' to show one process during 5 seconds;" << endl;
    cout << "'q' to quit;\n" << endl;
}

void ShowProcesses()
{
    printf("Parent process: %d \n", getpid());
    int k = 1;
    for(auto j: procInfo)
    {
        printf("%d.Child process: %d \n", k++, j);
    }
}

int main()
{

    showOptionList();

    initSignalHandlers();
    sprintf(parentPID, "%d", getpid());


    while (true)
    {
        switch(getchar())
        {
            case '+':
            {
                if(procInfo.size() < MAX_AMOUNT_OF_PROCESSES)
                {
                    addOneProcess();
                    if (Print == true)
                    {
                        napms(150);
                        kill(procInfo.back(), SIGUSR1);
                    }
                }
                break;
            }
            case '-':
                {
                if (!procInfo.empty())
                {
                    if (i == procInfo.size() - 1)
                    {
                        removeOneProcess();
                        raise(SIGUSR1);
                    }
                    else
                    {
                        removeOneProcess();
                    }
                }
                break;
            }
            case 'l':
            {
                ShowProcesses();
                break;
            }
            case 'k':
            {
                while (!procInfo.empty())
                {
                    removeOneProcess();
                }
                raise(SIGUSR1);
                break;
            }
            case 's':
            {
                printf("\n\n\nParametr (1, 2, 3, 4, 5) \n");
                switch(getchar())
                {
                    case '1':{printAvailable[0]=false; break;}
                    case '2':{printAvailable[1]=false; break;}
                    case '3':{printAvailable[2]=false; break;}
                    case '4':{printAvailable[3]=false; break;}
                    case '5':{printAvailable[4]=false; break;}
                    default: {Print = false;
                    for (int j = 0; j<MAX_AMOUNT_OF_PROCESSES; j++)
                        {
                            printAvailable[j]=false;
                        }  
                     break;}
                }
                break;
            }
            case 'g':
            {
                printf("\n\n\nParametr (1, 2, 3, 4, 5) \n");
                Print = true;
                switch(myGetch())
                {
                    
                    case '1':{printAvailable[0]=true; break;}
                    case '2':{printAvailable[1]=true; break;}
                    case '3':{printAvailable[2]=true; break;}
                    case '4':{printAvailable[3]=true; break;}
                    case '5':{printAvailable[4]=true; break;}
                    default: { 
                        
                        for (int j = 0; j<MAX_AMOUNT_OF_PROCESSES; j++)
                        {
                            printAvailable[j]=true;
                        }    
                        break;
                    }
                }
                raise(SIGUSR1);
                break;
            }
            case 'p':
            {
                for (int j = 0; j<MAX_AMOUNT_OF_PROCESSES; j++)
                {
                    printAvailable[j]=false;
                }  
                switch(myGetch())
                {
                   case '1':{printAvailable[0]=true; break;}
                    case '2':{printAvailable[1]=true; break;}
                    case '3':{printAvailable[2]=true; break;}
                    case '4':{printAvailable[3]=true; break;}
                    case '5':{printAvailable[4]=true; break;}
                }
                raise(SIGUSR1);
                napms(4000);
                 Print = true;
                  for (int j = 0; j<MAX_AMOUNT_OF_PROCESSES; j++)
                        {
                            printAvailable[j]=true;
                        }  
                break;
            }
            case 'q':
                {
                while (!procInfo.empty())
                {
                    removeOneProcess();
                }
                cout << "\nPress any key to proceed...\n";
                myGetch();
                return 0;
            }
        }
    }

    return 0;
}