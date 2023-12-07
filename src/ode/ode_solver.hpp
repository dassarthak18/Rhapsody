/*
odesolver is a header-only library for solving ODEs. It provides capabilities
for numerically solving ordinary differential equations (ODEs) of the form
dy/dt = f(t, y) where y is the state vector that evolves over time t according
to dynamics f.
*/

#pragma once

#include <vector>
#include <functional>

namespace ode
{
  class Solver
  {
    std::function<double(double, std::vector<double>)> func_;
    public:
      /*
      The main class exposed by the library is ode::Solver.
      The constructor takes the system dynamics function f as a std::function.
      */
      //Solver(std::function<double(double, std::vector<double>)> f) : func_(f) {}
      Solver(std::function<std::vector<double>(double, std::vector<double>)> f) : func_(f) {}
      std::vector<double> Solve(double t0, double tf, double dt, std::vector<double> y0);
  };
}

std::vector<double> ode::Solver::Solve(double t0, double tf, double dt, std::vector<double> y0)
/*
The main method for solving the ODE is Solve(), which advances the state in time
and returns the full state history. t0 is the initial time, tf is the final time,
dt is the integration timestep and y0 is the initial state vector.

The return is a vector containing interleaved time and state values that can be
easily plotted or analyzed.
*/
{
  std::vector<double> result;
  result.push_back(t0);
  for(int i = 0; i < y0.size(); ++i)
    result.push_back(y0[i]);
  double t = t0;
  std::vector<double> y = y0;
  while (t <= tf)
  {
    std::vector<double> dydt(y.size());
    for (int i = 0; i < y.size(); ++i)
      dydt[i] = func_(t, y);  
    for (int i = 0; i < y.size(); ++i)
      y[i] += dydt[i] * dt;
    result.push_back(t+dt);
    for (int i = 0; i < y.size(); ++i)
      result.push_back(y[i]);  
    t += dt;
  }
return result;
}