/*
plotter is a header-only library for plotting trajectories. It provides capabilities
for plotting trajectories passed to it via an external C++ wrapper for GNUPlot.
*/

#pragma once
#include <fstream>
#include<algorithm>
#include "gnuplot.h"
#include "../agents/VanillaAgent.hpp"

namespace plotter
{
  template<typename T>
  class Plotter
  {
    vector<pair<T, T> > yAxis, xAxis;
    string xvar, yvar;

    public:
      void Plot();

      /* We have the option to plot any two variables, or plot a variable against time.*/

      Plotter(VanillaAgent<T>& plottedAgent, string x_var_name, string y_var_name, vector<vector<pair<T, T> > > traj)
      {
        auto it = find(plottedAgent.ContVars.begin(), plottedAgent.ContVars.end(), x_var_name);
        int x_index = it - plottedAgent.ContVars.begin();
        it = find(plottedAgent.ContVars.begin(), plottedAgent.ContVars.end(), y_var_name);
        int y_index = it - plottedAgent.ContVars.begin();
        xAxis = traj[x_index];
        yAxis = traj[y_index];
        xvar = x_var_name;
        yvar = y_var_name;
      }

      Plotter(VanillaAgent<T>& plottedAgent, string var_name, vector<vector<pair<T, T> > > traj)
      {
        auto it = find(plottedAgent.ContVars.begin(), plottedAgent.ContVars.end(), var_name);
        int index = it - plottedAgent.ContVars.begin();
        yAxis = traj[index];
        xvar = "Time";
        yvar = var_name;
      }

      ~Plotter()
      {
        int result = remove("trajectory.dat");
      }
  };
}

/*
The main method for plotting the trajectory is Plot(), which simply passes
the trajectory to be plotted to GNUPlot via generation of an intermediary
data file.
*/
template<typename T>
void plotter::Plotter<T>::Plot()
{
  ofstream outfile;
  outfile.open("trajectory.dat",ios::trunc);
  for (int i = 0; i < yAxis.size(); i++)
  {
    pair<T, T> tup = yAxis[i]; 
    if (xAxis.empty())
    {
      string str = to_string(tup.first) + "  " + to_string(tup.second) + "\n";
      outfile << str;
    }
    else
    {
      pair <T, T> xtup = xAxis[i];
      string str = to_string(tup.first) + "  " + to_string(tup.second) + "  " + to_string(xtup.second) + "\n";
      outfile << str;
    }
  }
  outfile.close();
  GnuplotPipe gp;
  gp.sendLine("set term qt font \"Helvetica Neue\"");
  gp.sendLine("set xlabel \"" + xvar + "\"");
  gp.sendLine("set ylabel \"" + yvar + "\"");
  if (xAxis.empty())
  {
    gp.sendLine("plot 'trajectory.dat' using 1:2 with lines");
  }
  else
  {
    gp.sendLine("plot 'trajectory.dat' using 3:2 with lines");
  }
}
