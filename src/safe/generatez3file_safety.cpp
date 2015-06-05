#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include "../utils/primitive.h"
#include "../utils/readinputs.h"
#include "../utils/writeconstraints.h"
#include "writespecificationconstraints.h"
#include "generatez3file.h"
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

  writeCostConstraint(ofp, workspace);
  ofp << endl;  
 
  /* Write the specification constraints */
  writeFinalDestinationConstraints1(ofp, workspace);
  //writeFinalDestinationConstraints2(ofp, workspace);

  writeFormationConstraints(ofp, workspace);
  ofp << endl;  
  writePrecedenceConstraints(ofp, workspace);
  ofp << endl;
  writeDistanceConstraints(ofp, workspace);
  ofp << endl;


  /* Check the satisfiability of the constraints and output the model */
  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  writeOutputConstraints(ofp, workspace);
 
  ofp.close();
}
