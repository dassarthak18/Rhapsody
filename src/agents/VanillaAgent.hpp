#pragma once
#include <regex>
#include "../ode/ode_solver.hpp"

using namespace std;

class VanillaAgent
{ 
  public:
  	vector<string> ContVars;
  	vector<string> ContDynamics;
  	vector<double> CurrentState;
	vector<double> initLB;
	vector<double> initUB;

	vector<vector<pair<double, double> > > Simulate(double time_horizon, double time_step);

	virtual void DiscDynamics()
	{}
};

vector<vector<pair<double, double> > > VanillaAgent::Simulate(double time_horizon, double time_step)
{
	double t = 0;
	vector<vector<pair<double, double> > > trajectories;
	for (int i = 0; i < ContVars.size(); i++)
	{
		trajectories.push_back({{t, CurrentState[i]}});
	}

	while (t <= time_horizon)
	{
		vector<double> updated_vals;
		for (int i = 0; i < ContDynamics.size(); i++)
		{
			vector<string> tokens = split(ContDynamics[i], '=');
			string lhs = tokens[0];
			string rhs = tokens[1];
			for (int j = 0; j < ContVars.size(); j++)
			{
				regex e(ContVars[j]);
				rhs = regex_replace(rhs, e, to_string(CurrentState[j]));
			}
			string odestring = lhs + "=" + rhs;
			auto solver = ode::Solver(odestring);
			updated_vals.push_back(solver.compute_one_step(CurrentState[i], time_step));
		}

		for (int i = 0; i < ContVars.size(); i++)
		{
			CurrentState[i] = updated_vals[i];
		}

		DiscDynamics();
		t += time_step;
		for (int i = 0; i < ContVars.size(); i++)
		{
			trajectories[i].push_back({t, CurrentState[i]});
		}
	}

	return trajectories;
}