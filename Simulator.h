#include <iostream>
#include <string>
#include "Students.h"
#include "GenQueue.h"

using namespace std;

class Simulator
{
private:
  int lineType;
  int entryTime;
  int timeAtWindow;
  int numStudentsAtClockTick;
  int medianArrayElementCount;
  int idleArrayElementCount;

public:
  Simulator();//Constructor
  ~Simulator();//Destructor

  bool importFile(string file); //read file
  bool timeTracker(int t); // keeps track of overall time

  double meanTime(); // math for students
  double medianTime();
  int longestTime();
  int overTenTime();

  double meanIdleTime(); //math for registrar
  int longestIdleTime();
  int idleOverFiveTime();

  Students* *windowArray;// setting arrays
  GenQueue<Students*> studentQueue;

  GenQueue<int> waitStats;
  GenQueue<int> idleStats;

  int *medianArray;
  int *idleArray;

  int totalWindows;
  int totalStudents;
};
