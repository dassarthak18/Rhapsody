#include "VanillaAgent.hpp"

class BallAgent
{
  void DiscDynamics() override;
  
  public:

    BallAgent(double x0, double v0, double horizon, double step)
    {
      pair<double, double> State;

      State.first = "x";
      State.second = x0;
      ContVars.push_back(State);

      State.first = "v";
      State.second = v0;
      ContVars.push_back(State);

      ContDynamics.push_back("x'=v");
      ContDynamics.push_back("v'=-9.8");

      time_horizon = horizon;
      time_step = step;
    }
};

void BallAgent::DiscDynamics()
{
  if (ContVars[0] <= 0)
  {
    ContVars[0].second = 0;
    ContVars[1].second = -0.9*ContVars[1].second;
  }
}
