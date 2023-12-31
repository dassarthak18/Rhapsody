#pragma once
#include <random>
#include "VanillaAgent.hpp"

template<typename T>
class NPCAgent : public VanillaAgent<T>
{
  public:

    NPCAgent(T x0, T v0)
    {
      VanillaAgent<T>::initLB = {x0, v0};
      VanillaAgent<T>::initUB = {x0, v0};
      VanillaAgent<T>::ContVars = {"x", "v"};
      VanillaAgent<T>::CurrentState = {x0, v0};
      VanillaAgent<T>::ContDynamics = {"x'=v", "v'=0"};
    }

    NPCAgent(T xl, T xu, T vl, T vu)
    {
      VanillaAgent<T>::initLB = {xl, vl};
      VanillaAgent<T>::initUB = {xu, vu};
      VanillaAgent<T>::ContVars = {"x", "v"};

      std::random_device rd1;
      std::mt19937 gen1(rd1());
      std::uniform_real_distribution<> dis1(xl, xu);
      T x0 = dis1(gen1);

      std::random_device rd2;
      std::mt19937 gen2(rd2());
      std::uniform_real_distribution<> dis2(vl, vu);
      T v0 = dis2(gen2);

      VanillaAgent<T>::CurrentState = {x0, v0};
      VanillaAgent<T>::ContDynamics = {"x'=v", "v'=0"};
    }
};

template<typename T>
class CarAgent : public VanillaAgent<T>
{
  void DiscDynamics() override;
  
  public:
    vector<VanillaAgent<T>* > Others;
    CarAgent(T x0, T v0, T a0, vector<VanillaAgent<T>*> others)
    {
      VanillaAgent<T>::initLB = {x0, v0, a0};
      VanillaAgent<T>::initUB = {x0, v0, a0};
      VanillaAgent<T>::ContVars = {"x", "v", "a"};
      VanillaAgent<T>::CurrentState = {x0, v0, a0};
      VanillaAgent<T>::ContDynamics = {"x'=v", "v'=a", "a'=0"};
      Others = others;
    }

    CarAgent(T xl, T xu, T vl, T vu, T al, T au, vector<VanillaAgent<T>*> others)
    {
      VanillaAgent<T>::initLB = {xl, vl, al};
      VanillaAgent<T>::initUB = {xu, vu, au};
      VanillaAgent<T>::ContVars = {"x", "v", "a"};

      std::random_device rd1;
      std::mt19937 gen1(rd1());
      std::uniform_real_distribution<> dis1(xl, xu);
      T x0 = dis1(gen1);

      std::random_device rd2;
      std::mt19937 gen2(rd2());
      std::uniform_real_distribution<> dis2(vl, vu);
      T v0 = dis2(gen2);

      std::random_device rd3;
      std::mt19937 gen3(rd3());
      std::uniform_real_distribution<> dis3(al, au);
      T a0 = dis3(gen2);

      VanillaAgent<T>::CurrentState = {x0, v0, a0};
      VanillaAgent<T>::ContDynamics = {"x'=v", "v'=a", "a'=0"};
      VanillaAgent<T>::Others = others;
    }
};

template<typename T>
void CarAgent<T>::DiscDynamics()
{
  if (Others[0]->CurrentState[0] - VanillaAgent<T>::CurrentState[0] <= 5 && Others[0]->CurrentState[0] - VanillaAgent<T>::CurrentState[0] > 0 && VanillaAgent<T>::CurrentState[2] > 0)
  {
    VanillaAgent<T>::CurrentState[2] = -1*VanillaAgent<T>::CurrentState[2];
  }
  else if (Others[0]->CurrentState[0] - VanillaAgent<T>::CurrentState[0] >= 10 && VanillaAgent<T>::CurrentState[2] < 0)
  {
    VanillaAgent<T>::CurrentState[2] = -1*VanillaAgent<T>::CurrentState[2];
  }
  else if (VanillaAgent<T>::CurrentState[0] == Others[0]->VanillaAgent<T>::CurrentState[0])
  {
    VanillaAgent<T>::CurrentState[1] = 0;
    VanillaAgent<T>::CurrentState[2] = 0;
    Others[0]->CurrentState[1] = 0;
  }
}
