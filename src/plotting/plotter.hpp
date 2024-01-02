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
    VanillaAgent<T>* plottedAgent;
    vector<pair<T, T> > yAxis;
    vector<pair<T, T> > xAxis;

    public:
      void Plot();

      Plotter(VanillaAgent<T>* plottedAgent, string x_var_name, string y_var_name, vector<vector<pair<T, T> > > traj)
      {
        auto it = find(plottedAgent->ContVars.begin(), plottedAgent->ContVars.end(), x_var_name);
        int x_index = it - plottedAgent->ContVars.begin();
        it = find(plottedAgent->ContVars.begin(), plottedAgent->ContVars.end(), y_var_name);
        int y_index = it - plottedAgent->ContVars.begin();
        xAxis = traj[x_index];
        yAxis = traj[y_index];
      }

      Plotter(VanillaAgent<T>* plottedAgent, string var_name, vector<vector<pair<T, T> > > traj)
      {
        auto it = find(plottedAgent->ContVars.begin(), plottedAgent->ContVars.end(), var_name);
        int index = it - plottedAgent->ContVars.begin();
        yAxis = traj[index];
      }

      ~Plotter()
      {
        int result = remove("trajectory.dat");
      }
  };
}

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
  if (xAxis.empty())
  {
    gp.sendLine("plot 'trajectory.dat' using 1:2 with lines");
  }
  else
  {
    gp.sendLine("plot 'trajectory.dat' using 3:2 with lines");
  }
}
