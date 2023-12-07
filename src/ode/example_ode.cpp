/*
Using the odesolver library consists of:
1. Defining your system dynamics derivative as a string
2. Constructing a Solver instance, passing the string
3. Calling Solve() to integrate through time

Here is an example that solves the ODE x'=-2*x+2 from t = 0
to t = 100, with a timestep of 0.1. We plot the trajectory
using a C++ interface for GNUPlot.
*/

#include "ode_solver.hpp"
#include "gnuplot.h"
#include <fstream>

int main()
{
  // Solving the ODE
  string ode = "x'=-2*x+2";
  auto solver = ode::Solver(ode);
  pair<double, double> initial;
  initial.first = 0;
  initial.second = 0;
  auto trajectory = solver.Solve(100.0, 0.1, initial);

  // Writing the trajectory into a data file
  ofstream outfile;
  outfile.open("trajectory.dat",ios::trunc);
  for (pair<double, double> i : trajectory)
  {
    string str = to_string(i.first) + "  " + to_string(i.second) + "\n";
    outfile << str;
  }
  outfile.close();

  // Plotting using GNU
  GnuplotPipe gp;
  gp.sendLine("plot 'trajectory.dat' lt rgb 'red'");

  return 0;
}
