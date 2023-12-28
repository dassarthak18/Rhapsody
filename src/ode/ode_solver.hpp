/*
odesolver is a header-only library for solving ODEs. It provides capabilities
for numerically solving linear and affine ordinary differential equations (ODEs).
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(string input, char delimiter)
{
    string token;
    vector<string> tokens;
    stringstream ss(input);

    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> split(const string& input, const string& delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while ((end = input.find(delimiter, start)) != string::npos)
    {
        tokens.push_back(input.substr(start, end - start));
        start = end + delimiter.length();
    }

    if (start < input.length())
    {
        tokens.push_back(input.substr(start));
    }

    return tokens;
}

namespace ode
{
  class Solver
  {
    vector<double> coefficients;
    vector<double> extract_coefficients(string ode);

    public:
      /*
      The main class exposed by the library is ode::Solver.
      The constructor takes the system dynamics as a string
      of the format x'=a*x+b.
      */
      double compute_one_step(double x0, double time_step);
      vector<pair<double, double> > Solve(double time_horizon, double time_step, pair<double, double> y0);

      Solver(string str)
      {
        coefficients = extract_coefficients(str);
      }
  };
}

vector<double> ode::Solver::extract_coefficients(string ode)
{
  double a = 0, b = 0;
  vector<string> arr1 = split(ode, '=');
  string var = arr1[0];
  var.erase(var.size() - 1);
  string rhs = arr1[1];

  vector<string> arr2;
  if (rhs.find(var) == string::npos)
      b = stod(rhs);
  else if (rhs.find('+') != string::npos or rhs.find(var+'-') != string::npos)
  {
      arr2 = split(rhs, var);
      for (int i = 0; i < arr2.size(); i++)
          if (arr2[i].find('*') != string::npos)
              arr2[i].erase(remove(arr2[i].begin(), arr2[i].end(), '*'), arr2[i].end());
      if (arr2[0] == "-")
          arr2[0] = "-1";
      if (arr2[0] == "")
          arr2[0] = "1";
      a = stod(arr2[0]);
      b = stod(arr2[1]);
  }
  else
  {
      if (rhs.find('*') != string::npos)
      {
          arr2 = split(rhs, '*');
          a = stod(arr2[0]);
      }
      else if (rhs == var)
          a = 1;
      else
          a = -1;
  }

  vector<double> coefficients;
  coefficients.push_back(a);
  coefficients.push_back(b);

  return coefficients;  
}

double ode::Solver::compute_one_step(double x0, double time_step)
{
  if (coefficients[0] == 0 and coefficients[1] == 0)
    return x0;
  else if (coefficients[0] == 0)
    return x0 + coefficients[1]*time_step;
  else
  {
    double e = exp(1);
    double a = coefficients[0];
    double bdiva = coefficients[1]/a;
    return ((x0 + bdiva)*pow(e,a*time_step) - bdiva);
  }
}

vector<pair<double, double> > ode::Solver::Solve(double time_horizon, double time_step, pair<double, double> y0)
/*
The main method for solving the ODE is Solve(), which advances the state in time
and returns the full state history. The return is a vector containing interleaved
time and state values that can be easily plotted or analyzed.
*/
{
  vector<pair<double, double> > trajectory;
  trajectory.push_back(y0);
  int no_of_steps = time_horizon/time_step;
  double t = y0.first;
  double x = y0.second;
  for (int i = 0; i < no_of_steps; i++)
  {
    t += time_step;
    x = compute_one_step(x, time_step);
    pair<double, double> step;
    step.first = t;
    step.second = x;
    trajectory.push_back(step);
  }
  return trajectory;
}