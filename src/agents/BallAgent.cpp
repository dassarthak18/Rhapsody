#pragma once
#include <random>
#include "VanillaAgent.hpp"

template<typename T>
class BallAgent : public VanillaAgent<T>
{
  void DiscDynamics() override;
  
  public:

    BallAgent(T x0, T v0)
    {
	VanillaAgent<T>::initLB = {x0, v0};
	VanillaAgent<T>::initUB = {x0, v0};
	VanillaAgent<T>::ContVars = {"x", "v"};
	VanillaAgent<T>::CurrentState = {x0, v0};
	VanillaAgent<T>::ContDynamics = {"x'=v", "v'=-9.8"};
    }

    BallAgent(T xl, T xu, T vl, T vu)
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
      VanillaAgent<T>::ContDynamics = {"x'=v", "v'=-9.8"};
    }
};

/* ToDo: Comment on the discrete dynamics*/
template<typename T>
void BallAgent<T>::DiscDynamics()
{
  if (VanillaAgent<T>::CurrentState[0] <= 0)
  {
    VanillaAgent<T>::CurrentState[0] = 0;
    VanillaAgent<T>::CurrentState[1] = -0.9 * VanillaAgent<T>::CurrentState[1];
  }

}
