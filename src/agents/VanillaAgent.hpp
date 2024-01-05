#pragma once
#include <regex>
#include "../ode/ode_solver.hpp"

using namespace std;

/* Todo: have templated class. We can define types such as Rational to have
 * precise computation, and similarly use float type for lesser precision.
 * Certain agents may have discrete states representable with ints, bools.
 */
template<typename T>
class VanillaAgent
{
/*ToDo: Having public data members not recommended. Is data hiding imp for us?*/ 
  public:
  	vector<string> ContVars;
  	vector<string> ContDynamics;
  	vector<T> CurrentState;
	vector<T> initLB;
	vector<T> initUB;

	vector<vector<pair<T, T> > > Simulate(double time_horizon, double time_step);

	/* ToDo: Have another simulate method here which takes an arg n and simulates n trajectories from random starting points
     * Consider a parallel implementation of simulating n trajectories.
	 */

	/* Why virtual? I removed it and the override keyword in the derived class. It still works!*/
	void DiscDynamics(){}
};

template<typename T>
vector<vector<pair<T, T> > > VanillaAgent<T>::Simulate(double time_horizon, double time_step)
{
	double t = 0;
	vector<vector<pair<T, T> > > trajectories;
	for (int i = 0; i < ContVars.size(); i++)
	{
		trajectories.push_back({{t, CurrentState[i]}});
	}

	while (t <= time_horizon)
	{
		vector<T> updated_vals;
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

		copy(updated_vals.begin(),updated_vals.end(),CurrentState.begin());
		
		DiscDynamics();
		t += time_step;
		for (int i = 0; i < ContVars.size(); i++)
		{
			trajectories[i].push_back({t, CurrentState[i]});
		}
	}

	return trajectories;
}
