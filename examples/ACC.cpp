#include "../src/agents/CarAgent.cpp"
#include "../src/plotting/plotter.hpp"

int main()
{
  NPCAgent lead(10, 10);
  vector<VanillaAgent*> Others;
  Others.push_back(&lead);
  /* elaborate on the arguments*/
  CarAgent ego(8, 0, 28, Others);
  auto trajectories = ego.Simulate(100, 0.01);
  auto plotx = plotter::Plotter(trajectories[0]);
  plotx.Plot();
  int result = remove("trajectory.dat");
  return 0;
}
