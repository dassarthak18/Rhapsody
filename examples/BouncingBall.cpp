#include "../src/agents/BallAgent.cpp"
#include "../src/scenario/scenario.hpp"

int main()
{
  /* To create an agent, we pass the initial values
  of its continuous variables as argument. Here, as
  BallAgent is a pre-defined Agent type, we have continuous
  variables x and v whose initial values are set to be 10 and
  0 respectively.*/
  BallAgent<float> ball {10, 0};
  /* We now create a scenario for simulation and plot the trajectories of the agent's x with respect to time. */	
  Scenario<float> scenario;
  scenario.add_agent(&ball);

  /* The simulate() function takes as argument the time horizon -
  which is the time duration of the simulation. In our example,
  we have time horizon 20. */

  auto trajectories = scenario.Simulate(0, 20);

  /* We now plot the trajectories of the agent's x with respect to time. */
  /* TODO: Should plotter be templated? Or can we deduce the type of templated
  variable from the agent directly?*/

  scenario.Plot(0, "x", trajectories);
  /* We now plot the trajectories of the agent's v with respect to time. */
  scenario.Plot(0, "v", trajectories);
  /* We now plot the trajectories of the agent's v with respect to agent's x. */
  /* TODO: Add exception handling in cases where the variable name is not defined
  in the agent.cpp class. */

  scenario.Plot(0, "x", "v", trajectories);

  return 0;
}

