
#include "../src/agents/BallAgent.cpp"
#include "../src/plotting/plotter.hpp"

int main()
{
  /* elaborate on the arguments of the agent constructor*/
  BallAgent ball {10, 0};
  /* elaborate on the arguments of Simulate */
  /*Todo: Changing the time-step leads to wrong simulations. Need to fix this*/
  auto trajectories = ball.Simulate(20, 0.01);
  /* Pass the variable name instead of index to be plotted.
   * mention that this plotter plots the variable's progress againts time.
   */
  auto plotx = plotter::Plotter(trajectories[0]);
  plotx.Plot();
  int result = remove("trajectory.dat");
  auto plotv = plotter::Plotter(trajectories[1]);
  plotv.Plot();
  result = remove("trajectory.dat");
  return 0;
}

