
#include "../src/agents/BallAgent.cpp"
#include "../src/plotting/plotter.hpp"

int main()
{
  /* To create an agent, we pass the initial values
  of its continuous variables as argument. Here, as
  BallAgent is a pre-defined Agent type, we have continuous
  variables x and v whose initial values are set to be 10 and
  0 respectively.*/
  BallAgent<double> ball {10, 0};
  /* The simulate() function takes as argument the time horizon -
  which is the time duration of the simulation - and the time step -
  which is the time interval for each step of computation. In our example,
  we have time horizon 20 and time step 0.01. */
  /*Todo: Changing the time-step leads to wrong simulations. Need to fix this*/
  auto trajectories = ball.Simulate(20, 0.01);
  /* We now plot the trajectories of the agent's x with respect to time. */
  auto plotx = plotter::Plotter(&ball, "x", trajectories);
  plotx.Plot();
  /* We now plot the trajectories of the agent's v with respect to time. */
  auto plotv = plotter::Plotter(&ball, "v", trajectories);
  plotv.Plot();
  /* We now plot the trajectories of the agent's v with respect to agent's x. */
  auto plotxv = plotter::Plotter(&ball, "x", "v", trajectories);
  plotxv.Plot();
  return 0;
}

