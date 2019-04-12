#include <iostream>
#include <string>
#include "Simulator.h"

using namespace std;

int main(int argc, char** argv)
{
  Simulator s;

  if(argc < 2) // if no file in command line
  {
    cout << "ERROR: Please enter a valid file.\n" << endl;
  }

  else if(argc >= 2) // if there is a file
  {
    string file = argv[1];
    int currTime = 0;
    int openWindows = 0;
    bool running = true;

    if(s.importFile(file)) //check if file import works
    {
      while(running)
      {
        if(s.studentQueue.isEmpty())
        {
          int temp = 0;

          for(int i = 0; i < s.totalWindows; ++i)
          {
            if((s.windowArray[i]->windowTime) < 1)
            {
              temp++;
            }
          }
          if(temp == s.totalWindows)
          {
            running = false;
          }
        }
        for(int i = 0; i < s.totalWindows; ++i) //check windows, move students to windows
        {
          if(s.windowArray[i]->windowTime < 1) //window open
          {
            if(!s.studentQueue.isEmpty())
            {
              Students* student = s.studentQueue.vFront();

              if(student->entryTime <= currTime)
              {
                if(s.windowArray[i]->idleTime > 0) //check idle time of window, if !=0 add to idle time
                {
                  s.idleStats.enqueue(s.windowArray[i]->idleTime);
                }
                s.windowArray[i] = s.studentQueue.dequeue(); //move from queue to window
                s.waitStats.enqueue(s.windowArray[i]->queueTime); //adds time in line to stats
              }
            }
          }
        }
        currTime++; //time tracker increment
        s.timeTracker(currTime);
      }
      for(int i = 0; i < s.totalWindows; ++i)//unfilled windows remain idle
      {
        if(s.windowArray[i]->idleTime > 0)
        {
          s.idleStats.enqueue(s.windowArray[i]->idleTime);
        }
      }
      cout << "\nSimulation Completed" << endl; //printing
      cout << "\nStudent Calculations" << endl;
      cout << "Mean Student Wait Time: " << s.meanTime() << endl;
      cout << "Median Student Wait Time: " << s.medianTime() << endl;
      cout << "Longest Student Wait Time: " << s.longestTime() << endl;
      cout << "Students Waiting Over Ten Minutes: " << s.overTenTime() << endl;
      cout << "\nWindow Calculations" << endl;
      cout << "Mean Window Idle Time: " << s.meanIdleTime() << endl;
      cout << "Longest Window Idle Time: " << s.longestIdleTime() << endl;
      cout << "Idle Time Over Five Minutes: " << s.idleOverFiveTime() << endl;
    }
  }
  return 0;
}
