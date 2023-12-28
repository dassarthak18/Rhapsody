#pragma once
#include <random>
#include "VanillaAgent.hpp"

class NPCAgent : public VanillaAgent
{
  public:

    NPCAgent(double x0, double v0)
    {
      initLB = {x0, v0};
      initUB = {x0, v0};
      ContVars = {"x", "v"};
      CurrentState = {x0, v0};
      ContDynamics = {"x'=v", "v'=0"};
    }

    NPCAgent(double xl, double xu, double vl, double vu)
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
      ContDynamics = {"x'=v", "v'=0"};
    }
};

class CarAgent : public VanillaAgent
{
  void DiscDynamics() override;
  
  public:
    vector<VanillaAgent*> Others;
    CarAgent(double x0, double v0, double a0, vector<VanillaAgent*> others)
    {
      initLB = {x0, v0, a0};
      initUB = {x0, v0, a0};
      ContVars = {"x", "v", "a"};
      CurrentState = {x0, v0, a0};
      ContDynamics = {"x'=v", "v'=a", "a'=0"};
      Others = others;
    }

    CarAgent(double xl, double xu, double vl, double vu, double al, double au, vector<VanillaAgent*> others)
    {
      initLB = {xl, vl, al};
      initUB = {xu, vu, au};
      ContVars = {"x", "v", "a"};

      std::random_device rd1;
      std::mt19937 gen1(rd1());
      std::uniform_real_distribution<> dis1(xl, xu);
      double x0 = dis1(gen1);

      std::random_device rd2;
      std::mt19937 gen2(rd2());
      std::uniform_real_distribution<> dis2(vl, vu);
      double v0 = dis2(gen2);

      std::random_device rd3;
      std::mt19937 gen3(rd3());
      std::uniform_real_distribution<> dis3(al, au);
      double a0 = dis3(gen2);

      CurrentState = {x0, v0, a0};
      ContDynamics = {"x'=v", "v'=a", "a'=0"};
      Others = others;
    }
};

void CarAgent::DiscDynamics()
{
  if (Others[0]->CurrentState[0] - CurrentState[0] <= 5 && Others[0]->CurrentState[0] - CurrentState[0] > 0 && CurrentState[2] > 0)
  {
    CurrentState[2] = -1*CurrentState[2];
  }
  else if (Others[0]->CurrentState[0] - CurrentState[0] >= 10 && CurrentState[2] < 0)
  {
    CurrentState[2] = -1*CurrentState[2];
  }
  else if (CurrentState[0] == Others[0]->CurrentState[0])
  {
    CurrentState[1] = 0;
    CurrentState[2] = 0;
    Others[0]->CurrentState[1] = 0;
  }
}