# Rhapsody
A C++ library for modelling, simulation, and verification of multi-agent hybrid systems.

**TODO**:
* Implement a 2-agent ACC benchmark. In order to do so, need to create a Scenario object and transfer the simulate() function there. Start off with the BaseSensor variant, that is, all agents can see and modify all variables of other agents.
* Remove ugliness in Discrete Dynamics: Parsing or something midway?
* Avoid fixing the template in Scenario.
* Referencing issues in Scenario leads to DiscDynamics of VanillaAgent being called. How to resolve this?
