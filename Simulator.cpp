#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>
#include "Simulator.h"

using namespace std;

Simulator::Simulator()
{
  lineType = 1;
  entryTime = 0;
  timeAtWindow = 0;

  numStudentsAtClockTick = 0;
  medianArrayElementCount = 0;
  idleArrayElementCount = 0;

  totalWindows = 0;
  totalStudents = 0;
}

Simulator::~Simulator()
{
  delete [] windowArray;
  delete [] idleArray;
  delete [] medianArray;
}

bool Simulator::importFile(string file) //file reading
{
  string line;
  int lineNum = 1;

  ifstream inputStream;
  inputStream.open(file.c_str());

  try
  {
    getline(inputStream, line);
    totalWindows = atoi(line.c_str()); //converts number of windows to int

    windowArray = new Students*[totalWindows];

    for(int i = 0; i < totalWindows; ++i)
    {
      Students* student = new Students();
      windowArray[i] = student;
    }
    lineNum++;
  }
  catch(exception e)
  {
    cout << "Error" << endl;
    return false;
  }
  while(getline(inputStream, line))
  {
    switch(lineType)
    {
      case(1): //clock tics
      {
        try
        {
          entryTime = atoi(line.c_str()); // converts time of entry to int
          lineType++;
          lineNum++;
        }
        catch(exception e)
        {
          cout << "Error" << endl;
          return false;
        }
        break;
      }
      case(2): //num students
      {
        try
        {
          if(line != "")
          {
            numStudentsAtClockTick = atoi(line.c_str()); //converts number of students to int

            for(int i = 0; i < numStudentsAtClockTick; ++i)
            {
              getline(inputStream, line);
              lineNum++;

              try
              {
                timeAtWindow = atoi(line.c_str()); //time at window to int
              }
              catch(exception e)
              {
                cout << "Error" << endl;
                return false;
              }
              totalStudents++;

              Students* student = new Students(timeAtWindow, entryTime);

              studentQueue.enqueue(student);
            }
            lineType--;
          }
        }
        catch(exception e)
        {
          cout << "Error" << endl;
          return false;
        }
        break;
      }
      default:
        break;
    }
  }
  return true;
  }

  bool Simulator::timeTracker(int t)
  {
    for(int i = 0; i < totalWindows; ++i)
    {
      if(windowArray[i]->windowTime > 0) // decreases when student is at window
      {
        windowArray[i]->windowTime--;
      }
      else //increases when student is not at a window
      {
        windowArray[i]->idleTime++;
      }
    }
    if(!studentQueue.isEmpty())
    {
      ListNode<Students*> *curr = studentQueue.front;

      while(curr != NULL)
      {
        if(curr->data->entryTime < t)
        {
          curr->data->queueTime += 1;
        }
        curr = curr->next;
      }
    }
    return true;
  }

  double Simulator::meanTime()
  {
    ListNode<int> *curr = waitStats.front;

    double mnWait = 0;
    double sum = 0;
    double counter = 0;

    while(curr != NULL)
    {
      sum += curr->data;
      curr = curr->next;
      counter++;
    }
    if(counter == 0)
    {
      return 0;
    }
    mnWait = sum / counter;
    return mnWait;
  }

  double Simulator::medianTime()
  {
    ListNode<int> *curr = waitStats.front;

    double medWait = 0;
    medianArrayElementCount = 0;

    while(curr != NULL) //counting elements in median list
    {
      curr = curr->next;
      medianArrayElementCount++;
    }
    if(medianArrayElementCount == 0)
    {
      return 0;
    }
    else
    {
      medianArray = new int[medianArrayElementCount];
      curr = waitStats.front;

      for(int i = 0; i < medianArrayElementCount; ++i) //puts everything into array
      {
        medianArray[i] = curr->data;
        curr = curr->next;
      }
      sort(medianArray, medianArray + medianArrayElementCount); //puts values into ascending order

      if(medianArrayElementCount % 2 == 1) // odd number of elements
      {
        double d = 0;
        int r = 0;

        r = (medianArrayElementCount/2) +1;
        d = medianArray[r];
        return d;
      }
      else // if even elements, find average
      {
        double d = 0;
        int a = 0;
        int z = 0;

        a = medianArrayElementCount / 2;
        z = (medianArrayElementCount / 2) + 1;

        if(medianArray[z] == 0)
        {
          return 0;
        }
        d = double(medianArray[a]) / double(medianArray[z]);
        return d;
      }
    }
  }

  int Simulator::longestTime()
  {
    if(medianArrayElementCount == 0)
    {
      return 0;
    }
    else
    {
      return medianArray[medianArrayElementCount - 1]; //return last element sorted
    }
  }

  int Simulator::overTenTime() // check array for values over 10
  {
    if(medianArrayElementCount == 0)
    {
      return 0;
    }
    else
    {
      int temp = 0;

      for(int i = 0; i < medianArrayElementCount; ++i)
      {
        if(medianArray[i] > 10)
        {
          ++temp;
        }
      }
      return temp;
    }
  }

double Simulator::meanIdleTime()
{
  ListNode<int> *curr = idleStats.front;

  double mnIdle = 0;
  double sum = 0;
  double counter;

  while(curr != NULL)
  {
    sum += curr->data;
    curr = curr->next;
    counter++;
  }
  if(counter == 0)
  {
    return 0;
  }
  mnIdle = sum / counter;
  return mnIdle;
}

int Simulator::longestIdleTime()
{
  ListNode<int> *curr = idleStats.front;

  idleArrayElementCount = 0;

  while(curr != NULL) //counting elements
  {
    curr = curr->next;
    idleArrayElementCount++;
  }
  idleArray = new int[idleArrayElementCount];

  curr = idleStats.front;

  for(int i = 0; i < idleArrayElementCount; ++i)//into array
  {
    idleArray[i] = curr->data;
    curr = curr->next;
  }
  sort(idleArray, idleArray + idleArrayElementCount);// sort in ascending order
  return(idleArray[idleArrayElementCount -1]);
}

int Simulator::idleOverFiveTime()
{
  int temp = 0;

  for(int i = 0; i < idleArrayElementCount; ++i)
  {
    if(idleArray[i] > 5)
    {
      ++temp;
    }
  }
  return temp;
}
