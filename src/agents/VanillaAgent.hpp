#pragma once

#include <bits/stdc++.h>
#include <regex>
#include "../ode/ode_solver.hpp"

using namespace std;

class VanillaAgent
{ 
  public:
  	vector<pair<string, double>> ContVars;
	vector<string> ContDynamics;
	void Simulate(double time_horizon, double time_step);

	void DiscDynamics()
	{}
};

void VanillaAgent::Simulate(double time_horizon, double time_step)
{
	double t = 0;
	cout<<"At t = "<<t<<", we have:\n";
	for (int i = 0; i < ContVars.size(); i++)
	{
		cout<<ContVars[i].first<<" = "<<ContVars[i].second<<"\n";
	}

	while (t <= time_horizon)
	{
		vector<double> updated_vals;
		for (int i = 0; i < ContDynamics.size(); i++)
		{
			tokens = split(ContDynamics[i], '=');
			lhs = tokens[0];
			rhs = tokens[1];
			vector<string> vars;
			vector<double> vals;
			for (auto j : ContVars)
			{
				vars.push_back(j.first);
				vals.push_back(j.second);
			}
			for (int j = 0; j < vars.size(); j++)
			{
				regex e(vars[j]);
				rhs = regex_replace(rhs, e, to_string(vals[j]));
			}
			string odestring = lhs + "=" + rhs;
			auto solver = ode::Solver(odestring);
			updated_vals.push_back(solver.compute_one_step(vals[i], time_step));
		}

		for (int i = 0; i < ContVars.size(); i++)
		{
			ContVars[i].second = updated_vals[i];
		}

		DiscDynamics();
		t += time_step;

		cout<<"At t = "<<t<<", we have:\n";
		for (int i = 0; i < ContVars.size(); i++)
		{
			cout<<ContVars[i].first<<" = "<<ContVars[i].second<<"\n";
		}
	}
}
