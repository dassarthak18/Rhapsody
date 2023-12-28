# Rhapsody
A C++ library for modelling, simulation, and verification of multi-agent hybrid systems.

**TODO**:
* Implement a 2-agent ACC benchmark. In order to do so, need to create a Scenario object and transfer the simulate() function there. Start off with the BaseSensor variant, that is, all agents can see and modify all variables of other agents. Consequently, the function DiscDynamics() must pass as argument all the other agents as objects. Must ensure that the non-ego agents in a decision logic can be accessed by their name or index.
