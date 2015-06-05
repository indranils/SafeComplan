#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;


float extractTrajectoryCostInformation()
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string value;
  string str;
  float val1, val2;
  float cost = 0.0;

  ifp.open("z3_output");
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 3);
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        if (var == "total_cost")
        {
          value = line.substr(location + 4);
          location = value.find(' ');
          str = value.substr(0, location - 1);
          val1 = atof(str.c_str());
          str = value.substr(location + 1);
          val2 = atof(str.c_str());
          cost = val1 / val2;
        }
      }
    }
  }
  ifp.close();
  return cost;
}


void extractTrajectoryVelocityInformation(string filename, vector< vector<int> > & velocities)
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string index;
  int value;
  int robot, time;

  cout << filename << endl;
  ifp.open(filename.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        istringstream (line.substr(location + 1)) >> value;
        location = var.find("vel_i_");
        if (location != -1)
        {
          index = var.substr(location + 6);
          location = index.find('_');
          if (location != -1)
          {
            //cout << "line=" << line << "--" << endl; 
            //cout << "var=" << var << "--" << endl; 
            //cout << "value=" << value << endl;
            //cout << "index=" << index << "--" << endl;
            istringstream (index.substr(0, location)) >> robot;
            istringstream (index.substr(location + 1)) >> time;
            //cout << "robot=" << robot << endl;
            //cout << "time=" << time << endl;
            if (robot > velocities.size())
            {
              velocities.resize(robot);
            }
            velocities[robot - 1].push_back(value);
          }
          else
          {
            cout << "parsing error 3.." << endl;
            exit(0);
          }
        }
      }
      else
      {
        cout << "parsing error 1.." << endl;
        exit(0);
      }
    }
  }
  ifp.close();
}
