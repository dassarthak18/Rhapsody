#pragma once
#include <random>
#include "VanillaAgent.hpp"

class BallAgent : public VanillaAgent
{
  void DiscDynamics() override;
  
  public:

    BallAgent(double x0, double v0)
    {
      initLB = {x0, v0};
      initUB = {x0, v0};
      ContVars = {"x", "v"};
      CurrentState = {x0, v0};
      ContDynamics = {"x'=v", "v'=-9.8"};
    }

    BallAgent(double xl, double xu, double vl, double vu)
    {
      initLB = {xl, vl};
      initUB = {xu, vu};
      ContVars = {"x", "v"};

      std::random_device rd1;
      std::mt19937 gen1(rd1());
      std::uniform_real_distribution<> dis1(xl, xu);
      double x0 = dis1(gen1);

      std::random_device rd2;
      std::mt19937 gen2(rd2());
      std::uniform_real_distribution<> dis2(vl, vu);
      double v0 = dis2(gen2);

      CurrentState = {x0, v0};
      ContDynamics = {"x'=v", "v'=-9.8"};
    }
};

void BallAgent::DiscDynamics()
{
  if (CurrentState[0] <= 0)
  {
    CurrentState[0] = 0;
    CurrentState[1] = -0.9*CurrentState[1];
  }
}