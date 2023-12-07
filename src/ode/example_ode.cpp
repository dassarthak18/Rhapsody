/*
Using the odesolver library consists of:
1. Defining your system dynamics derivative function f
2. Constructing a Solver instance, passing f
3. Calling Solve() to integrate through time

Here is an example that solves the ODE dy/dt = 1
from t = 0 to t = 10, with a timestep of 1.
*/

#include "ode_solver.hpp"
#include <functional>

std::vector<double> f(double t, std::vector<double> y)
{
  std::vector<double> dydt;
  dydt.push_back(1.0);
  return dydt;
}

int main()
{
  std::function<double(double, std::vector<double>)> func = f;
  ode::Solver solver(func);
  auto solution = solver.Solve(0.0, 10.0, 0.1, {1.0, 0.0});
}