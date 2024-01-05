/*
scenario is a header-only library that serves as a wrapper for the simulation and
plotting functionalities of every agent in one place, ultimately acting as a
multi-agent hybrid system.
*/

#pragma once
#include "../agents/VanillaAgent.hpp"
#include "../plotting/plotter.hpp"


template<class T>
class Scenario
{
  vector<VanillaAgent<T>* > scenario_agents;

  public:

	vector<vector<pair<T, T> > > Simulate(int index, double time_horizon);
    void Plot(int index, string var, vector<vector<pair <T, T> > > trajectories);
    void Plot(int index, string var1, string var2, vector<vector<pair <T, T> > > trajectories);

	/* constructs an empty scenario */
	Scenario(){}

	/* initialises with a list of agents */
    Scenario(vector<VanillaAgent<T> > agents)
    {
      scenario_agents = agents;
    }

	/* Adds an agent to the scenario */
	void add_agent(VanillaAgent<T>* new_agent){
		scenario_agents.push_back(new_agent);
	}

};

template<typename T>
vector<vector<pair <T, T> > > Scenario<T>::Simulate(int index, double time_horizon)
{
  auto traj = scenario_agents[index]->Simulate(time_horizon);
  return traj;
}

template<typename T>
void Scenario<T>::Plot(int index, string var, vector<vector<pair <T, T> > > trajectories)
{
  plotter::Plotter<T> plotx(scenario_agents[index], var, trajectories);
  plotx.Plot();
}

template<typename T>
void Scenario<T>::Plot(int index, string var1, string var2, vector<vector<pair <T, T> > > trajectories)
{
  plotter::Plotter<T> plotx(scenario_agents[index], var1, var2, trajectories);
  plotx.Plot();
}


