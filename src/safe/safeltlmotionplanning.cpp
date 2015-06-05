#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../utils/primitive.h"
#include "../utils/readinputs.h"
#include "../utils/writeconstraints.h"
#include "../utils/generatetrajectory.h"
#include "writespecificationconstraints.h"

using namespace std;


void generateZ3File(prim_vec_t primitives, pos_vec_t obstacles, workspace_t workspace)
{
  ofstream ofp;

  ofp.open("constraints.smt2");

  /* Declare the variables */
  declareVariables(ofp, workspace);


  /* Write the General Constraints */
  writeInitialLocationConstraints(ofp, workspace);
  ofp << endl;

  writeObstacleConstraints(ofp, obstacles, workspace);
  ofp << endl;

  writeTransitionConstraints(ofp, primitives, obstacles, workspace);
  ofp << endl;

  writeCollisionAvoidanceConstraints2(ofp, primitives, workspace);
  ofp << endl;

  writeDistanceConstraints(ofp, workspace);
  ofp << endl;
  
  writeCostConstraint(ofp, workspace);
  ofp << endl;

  /* Write the specification constraints */
  writeFinalDestinationConstraints1(ofp, workspace);
  //writeFinalDestinationConstraints2(ofp, workspace);

  writeFormationConstraints(ofp, workspace);
  ofp << endl;
  writePrecedenceConstraints(ofp, workspace);
  ofp << endl;


  /* Check the satisfiability of the constraints and output the model */
  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  writeOutputConstraints(ofp, workspace);

  ofp.close();
}


int main ()
{
  prim_vec_t primitives;
  pos_vec_t obstacles;
  workspace_t workspace;
  prim_cost_t prim_cost;
  char command[100];
  int trajectory_length;

  readPrimitives(primitives);
  //writePrimitives(primitives);

  getPrimitiveCost(primitives, prim_cost);
  writePrimitiveCost(prim_cost);

  readObstacles(obstacles);
  //writeObstacles(obstacles);

  readWorkspace(workspace);
  //writeWorkspace(workspace);

  sprintf(command, "time ./formula_simplifier input");
  system(command);

  struct timeval tm;
  double wcts, wcte;
  ofstream ofp;

  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  trajectory_length = generateTrajectory(primitives, prim_cost, obstacles, workspace);
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("result", fstream::app);
  ofp << "Total Time Before Optimization = ";
  ofp.close();
  printTimeDifference(wcts, wcte);

  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  optimizeTrajectory(primitives, prim_cost, obstacles, workspace, trajectory_length);
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("result", fstream::app);
  ofp << "Total Time For Optimization = ";
  ofp.close();
  printTimeDifference(wcts, wcte);
}
