/*
Using the odesolver library consists of:
1. Defining your system dynamics derivative as a string
2. Constructing a Solver instance, passing the string
3. Calling Solve() to integrate through time

Here is an example. We plot the trajectory
using a C++ interface for GNUPlot.
*/

#include "ode_solver.hpp"
#include "gnuplot.h"
#include <fstream>

int main()
{

  // Input
  string ode;
  double time_horizon, time_step, t0, x0;
  cout<<"Enter the ODE to solve: ";
  getline (cin, ode);
  cout<<"Enter the time horizon: ";
  cin>>time_horizon;
  cout<<"Enter the time step for computation: ";
  cin>>time_step;
  cout<<"Enter the initial time: ";
  cin>>t0;
  cout<<"Enter the initial x value: ";
  cin>>x0;

  // Solving the ODE
  auto solver = ode::Solver(ode);
  pair<double, double> initial;
  initial.first = t0;
  initial.second = x0;
  auto trajectory = solver.Solve(time_horizon, time_step, initial);

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
