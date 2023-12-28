/*
The simulate function follows the algorithm:
  while t <= time_horizon:
  {
    initial x, v
    replace ODE variables in RHS with current values
    compute for one step and update x, v
    run 1 pass of discrete dynamics
  }
  print the plot of the trajectory
*/

#include <vector>
#include <string>
#include <bits/stdc++.h>

class VanillaAgent
{ 
  public:
  	vector<pair<string, double>> ContVars;
	vector<string> ContDynamics;
	double time_horizon, time_step;
	void Simulate();

	void DiscDynamics()
	{}

    VanillaAgent(double horizon, double step)
    {
    	time_horizon = horizon;
		time_step = step;
    }
};

void VanillaAgent::Simulate()
{
	
}
