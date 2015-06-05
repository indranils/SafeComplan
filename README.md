# SafeComplan
Compositional Multi-Robot Motion Planner for Safe LTL Specifications

WORKSPACE

The workspace is represented as a 3D occupancy grid map, where we decompose the workspace into 
blocks using a uniform grid. We specify the size of the workspace by the number of blocks in each 
dimension.Each block is assigned a unique identifier. The identifier of the lower left block is 
assigned the identifier $(0,0,0)$. If the identifier of a block is ID = (I_x, I_y, I_z), where I_x,
I_y and I_z are non-negative integers, then the identifiers of the neighboring blocks are obtained 
by adding or subtracting 1 to the appropriate component(s) of ID. The unit of distance is 1 block 
in the workspace. The distance between two blocks with identifier ID_1 = (I_x_1, I_y_1, I_z_1) and
ID_1 = (I_x_2, I_y_2, I_z_2) is given by dist(ID_1, ID_2) = (I_x_2 - I_x_1 , I_y_2 - I_y_1, I_z_2 -
I_z_1). Each block may either be free, or may be occupied by an obstacle.  



HOW TO PREPARE INPUT FILES?

Before running Complan, you have to prepare a few input files. These files are placed in examples 
folder.


1. The first one is 2d_templete.txt which contains the motion primitives to be used in trajectory
planning. Each entry of this file represents a motion primitive and has the following fields

%%%%%%%%
ID
q_i
q_f
pos_f
cost
duration
swath 
%%%%%%%%

Here ID denotes the ID of the primitive starting from 1. q_i and q_f denote the initial and final 
velocity configuration. pos_f denotes the distance of the final position of the robot from the 
position where the motion primitive is applied. "cost" denotes an estimated cost for executing the
precomputed control law for "duration" amount of time in free space. W denotes the set of relative 
blocks through which the robot passes to move from its initial location to its final location.


2. The second one of them is workspace.txt that contains some necessary information about the 
experiment. The entries of workspace.txt file are given below:

%%%%%%%%%
x_max
y_max
N
x_init_1
....
x_init_N
y_init_1
..
y_init_N
L
Cost
%%%%%%%%%

Here x_max and y_max denote the maximum x and y-coordinate. N denotes the number of robots. 
x_init_1 to x_init_N denote the x-coordenates of the initial locations of the robots. y_init_1 to 
y_init_N denote the y-coordinates of the final locations of the robots. L denotes the length of the
trajectory. Cost is the maximum total allowable cost to synthesize the trajectories.


3. The third input file is obstacle.txt. Each entry of this file is a co-ordinate of a block in the
workspace that is occupied by the obstacles.



HOW TO RUN THE TOOL?

Having these three input files ready, you can now use the following command to generate an input 
file for Z3 SMT solver.

./run.sh tool_z3

This command generates a file named constraints.smt2. This file can be given as input to Z3 SMT 
solver using the following command:

z3 constraint.smt2 > z3_output

The output of Z3 is stored in file named z3_output. The file z3_output stores the output of the solver.

The state of the robots, i.e., their location and velocity configuration at the discrete points on 
the trajectories can be extracted from z3_output using the following command:

perl processoutputfile.pl

This command stores the state of the robots at the discrete points on the trajectories in a file 
named planner_output. This file can be used to send the robots the required commands to move them 
from their initial locations to their final locations.


HOW TO ADD DIFFERENT FINAL DESTINATION CONSTRAINTS AND SAFETY CONSTRAINTS? 

After generating constrains.smt2 file, we can add additional constraints to specify final 
destinations of the robots or to impose a set of safety constraints. The only thing that you need 
to know is what variable names we use internally to represent different discrete points on the 
trajectories. The x-coordinate of the i-th robot at the j-th discrete point is denoted by x_i_j. 
If you want to say that the y-coordinate of the final destination of robot 3 has to be betwwen 18 
and 20, and you have specified the number of discrete points on the trajectory N to be equal to 15
in workspace.txt file, then the foolowing line has to be added to constraints.smt2 file.

(assert (and (>= y_3_15 18) (<= y_3_15 20)))

By default, the function writeFinalDestinationConstraints1(ofp, workspace) in the src directory is 
used to add constraints to capture the destination locations as specified in workspace.txt file. If
you want to add constraints to capture richer specification on the destination locations of the 
robots in constraints.smt2 file, then bfore running run.sh file go to the src directory and comment
out the function writeFinalDestinationConstraints1(ofp, workspace).


Similarly, it is easy to add an invariant specification in constraints.smt2 file. For example, 
suppose the specification says that the x-coordinate of robot 3 has to be always between 5 and 15.
If you have specified the number of discrete points on the trajectory N to be equal to 15 in 
workspace.txt file, then the foolowing lines have to be added to constraints.smt2 file to capture 
the invariant specification.
 
(assert (and (>= x_3_1 5) (<= x_3_1 15)))
(assert (and (>= x_3_2 5) (<= x_3_2 15)))
....
(assert (and (>= x_3_15 5) (<= x_3_15 15)))



HOW TO GENERATE OPTIMAL TRAJECTORY?

The current version of Complan does not support generating optimal trajectories automatically.
To generate optimal cost trajectories, you can perform a binary search for the optimal cost. to see
how to select the range for the binary search, please refer to our IROS 2014 paper. 

Once you have selected the range for search, you can call Complan iteratively after setting 
different value for cost in workspace.txt file. To understand how to update the value of cost, refe
to Section III.D. of our IROS 2014 paper. 


HOW TO RUN THE EXAMPLES IN THE IROS 2014 PAPER?

In our IROS 2014 paper, we have two examples. To synthesize trajectories for these two examples,
you have to go inside the src directory and uncomment proper functions.

For example 1, uncomment the following functions:

writeFinalDestinationConstraints1(ofp, workspace);
writeFormationConstraints(ofp, workspace);
writePrecedenceConstraints(ofp, workspace);
writeDistanceConstraints(ofp, workspace);

For example 2, uncomment the following two functions:

writeFinalDestinationConstraints2(ofp, workspace);
writeDistanceConstraints(ofp, workspace);

Once the required functions have been uncommented, go back to the examples directory, and run 
run.sh in the way described above.



HOW TO REMOVE THE GENERATED FILES DURING AN EXPERIMENT?

The file clean.sh can be run to delete all files generated during an experiment.
