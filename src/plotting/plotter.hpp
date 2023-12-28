#pragma once
#include <fstream>
#include "gnuplot.h"

namespace plotter
{
  class Plotter
  {
    vector<pair<double, double> > trajectory;

    public:
      void Plot();

      Plotter(vector<pair<double, double> > traj)
      {
        trajectory = traj;
      }
  };
}

void plotter::Plotter::Plot()
{
  ofstream outfile;
  outfile.open("trajectory.dat",ios::trunc);
  for (pair<double, double> i : trajectory)
  {
    string str = to_string(i.first) + "  " + to_string(i.second) + "\n";
    outfile << str;
  }
  outfile.close();
  GnuplotPipe gp;
  gp.sendLine("plot 'trajectory.dat' with lines");
}