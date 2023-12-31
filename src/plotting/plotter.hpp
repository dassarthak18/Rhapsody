#pragma once
#include <fstream>
#include "gnuplot.h"

namespace plotter
{
  template<typename T>
  class Plotter
  {
    vector<pair<T, T> > trajectory;

    public:
      void Plot();

      /* Have a constructor to take the variable name to plot vs time*/
      /* Have a generic constructor that takes two variables of the system to plot*/
      Plotter(vector<pair<T, T> > traj)
      {
        trajectory = traj;
      }
  };
}

template<typename T>
void plotter::Plotter<T>::Plot()
{
  ofstream outfile;
  outfile.open("trajectory.dat",ios::trunc);
  for (pair<T, T> i : trajectory)
  {
    string str = to_string(i.first) + "  " + to_string(i.second) + "\n";
    outfile << str;
  }
  outfile.close();
  GnuplotPipe gp;
  gp.sendLine("plot 'trajectory.dat' with lines");
}
