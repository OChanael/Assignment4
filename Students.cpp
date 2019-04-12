#include <iostream>
#include "Students.h"

using namespace std;

Students::Students()
{
  windowTime = 0;
  entryTime = 0;
  queueTime = 0;
  idleTime = 0;
}

Students::Students(int t, int e)
{
  windowTime = t;
  entryTime = e;
  queueTime = 0;
  idleTime = 0;
}

Students::~Students()
{

}
