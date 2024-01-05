#include "../src/agents/CarAgent.cpp"
#include "../src/scenario/scenario.hpp"

/* How to model an ACC with more than 2 cars? Can our library support that? */

int main()
{
  /* To create an agent, we pass the initial values
  of its continuous variables as argument. Here, as
  NPCAgent is a pre-defined Agent type, we have continuous
  variables x and v whose initial values are set to be 10 and
  10 respectively.*/
  NPCAgent<double> lead(10, 10);
  vector<VanillaAgent<double> > Others; // This is our "other" agent.
  Others.push_back(lead);
  /* For our second agent of type CarAgent,
  the initial values are set to be x = 8, v = 0, a = 28.
  It also takes as argument all the other agents in the
  environment. This is our temporary stand-in of having
  a basic default sensor.*/
  CarAgent<double> ego(8, 0, 28, Others); // This is the main agent we are interested in.
  /* We now create a scenario for simulation and plot the trajectories of the agent's x with respect to time. */
  vector<VanillaAgent<double> > Agents;
  Agents.push_back(ego);
  Agents.push_back(lead);
  Scenario<double> scenario(Agents);
  auto trajectories = ego.Simulate(100);
  //auto trajectories = scenario.Simulate(0, 100);
  scenario.Plot(0, "x", trajectories);
  return 0;
}
