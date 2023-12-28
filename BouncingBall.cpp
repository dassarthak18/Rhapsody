#include "src/agents/BallAgent.cpp"

int main()
{
  BallAgent ball(0,0);
  ball.Simulate(20, 0.1);
  return 0;
}