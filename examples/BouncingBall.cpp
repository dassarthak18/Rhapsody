#include <cstdio>
#include "../src/agents/BallAgent.cpp"
#include "../src/plotting/plotter.hpp"

int main()
{
  BallAgent ball(10, 0);
  auto trajectories = ball.Simulate(20, 0.01);
  auto plotx = plotter::Plotter(trajectories[0]);
  plotx.Plot();
  int result = remove("trajectory.dat");
  auto plotv = plotter::Plotter(trajectories[1]);
  plotv.Plot();
  int result = remove("trajectory.dat");
  return 0;
}