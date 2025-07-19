# Rhapsody
A C++ library for modelling, simulation, and verification of multi-agent hybrid systems. Rhapsody extends the multi-agent hybrid systems model proposed in the [Verse library](https://github.com/AutoVerse-ai/Verse-library) to support shared variables, indexing of agents, support for continuous dynamics of agents which depend on the continuous variables of other agents, and scalability to non-deterministic systems such as statistical ensembles.

## Libraries Used

The following libraries are included in ``src/include`` directory:

* **[JSON for Modern C++](https://github.com/nlohmann/json).** C++ header-only library for parsing JSON format files.
* **[Runge-Kutta ODE Solver](https://github.com/davidrzs/Runge-Kutta-ODE-Solver/tree/master).** Lightweight C++ header-only library providing explicit RK solvers for ODEs.
* **[gnuplot-cpp](https://github.com/martinruenz/gnuplot-cpp).** Lightweight C++ wrapper for GNUPlot, used to plot simulation traces for agents.

## Dependencies

The following dependencies must be manually installed:

* **[Eigen](https://github.com/PX4/eigen).** Linear algebra library required by Runge-Kutta ODE Solver. Can be installed on Debian-based systems via ``sudo apt install libeigen3-dev`` and on RPM based systems via ``sudo dnf install eigen3-devel``.
* **[GNUPlot](http://www.gnuplot.info/).** Plotting library required by gnuplot-cpp. Can be installed on Debian-based systems via ``sudo apt install gnuplot`` and on RPM based systems via ``sudo dnf install gnuplot``.

## TODO
* Implement a 3-agent ACC benchmark. For that do we need to define a new agent?
* Implement the NRS. Have a dummy agent to store shared variables.
* Simulate all agents together in a scenario.
* Have another simulate method here which takes an arg n and simulates n trajectories from random starting points. Consider a parallel implementation of simulating n trajectories.
* Remove ugliness in Discrete Dynamics: Parsing or something midway?
* Avoid fixing the template in Scenario

