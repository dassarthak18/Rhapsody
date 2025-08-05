# Rhapsody
A C++ library for modelling, simulation, and verification of multi-agent hybrid systems. Rhapsody extends the multi-agent hybrid systems model proposed in the [Verse library](https://github.com/AutoVerse-ai/Verse-library) to support shared variables, indexing of agents, support for continuous dynamics of agents which depend on the continuous variables of other agents, and scalability to non-deterministic systems such as statistical ensembles.

## Table of Contents
- [Libraries Used](#libraries-used)
- [Dependencies](#dependencies)
- [Example Usage](#example-usage)
- [TODO](#todo)

## Libraries Used

The following libraries are included in ``src/include`` directory:

* **[gnuplot-cpp](https://github.com/martinruenz/gnuplot-cpp).** Lightweight C++ wrapper for GNUPlot, used to plot simulation traces for agents.
* **[JSON for Modern C++](https://github.com/nlohmann/json).** C++ header-only library for parsing JSON format files.
* **[Runge-Kutta ODE Solver](https://github.com/davidrzs/Runge-Kutta-ODE-Solver/tree/master).** Lightweight C++ header-only library providing explicit RK solvers for ODEs.

## Dependencies

The following dependencies must be manually installed:

* **[Eigen](https://github.com/PX4/eigen).** Linear algebra library required by Runge-Kutta ODE Solver. Can be installed on Debian-based systems via ``sudo apt install libeigen3-dev`` and on RPM based systems via ``sudo dnf install eigen3-devel``.
* **[GNUPlot](http://www.gnuplot.info/).** Plotting library required by gnuplot-cpp. Can be installed on Debian-based systems via ``sudo apt install gnuplot`` and on RPM based systems via ``sudo dnf install gnuplot``.

## Example Usage

``examples/bouncing_ball.json`` illustrates the basic idea of how to define a hybrid system as a JSON:

```json5
{
    "environment": "BouncingBall", // Name of the environment
    "agents": { // Description of the agent classes
            "Ball": {
                "vars": ["y", "vy"], // Each agent has a set of continuous variables
                "modes": {
                    "FALLING": {"invariants": ["y >= 0"], "flow": ["y'= vy", "vy' = -9.8"]} // Each agent has a set of modes, each with their own invariants and flow (linear and affine ODEs are supported)
                }
            }
        },    
    "instances": {"Ball1": "Ball"}, // An environment may consist of multiple agents
    "init": {
        "Ball1": {"mode": "FALLING", "vy": 0.0, "y": [10.0, 20.0]} // The initial state of the environment
    },
    "transitions": { // Each agent has their own set of transitions, each with their own guard and resets (support for indexing of agents)
    "Ball1": [{"from": "FALLING",
                "to": "FALLING",
                "when": ["Ball1.y <= 0", "Ball1.vy < 0"],
                "reset": {"Ball1.vy": "-0.9 * Ball1.vy"}
            }]
    },
    "verify": {"time_horizon": 10.0, "time_step": 0.01}, // The time step and time horizon for simulation and verification
    "assert": ["Ball1.y >= 0"] // Safety criteria
}
```

## Publications

* **Dec 2024 (Preprint.)** Das, S. Modeling and Verification of Multi-Agent Cyber-Physical Systems in Verse Library. _TechRxiv_. [DOI: 10.36227/techrxiv.172470839.93311927/v2](https://www.techrxiv.org/users/816050/articles/1216819-modeling-and-verification-of-multi-agent-cyber-physical-systems-in-verse-library)

## TODO
* Implement a 3-agent ACC benchmark. For that do we need to define a new agent?
* Implement the NRS. Have a dummy agent to store shared variables.
* Simulate all agents together in a scenario.
* Have another simulate method here which takes an arg n and simulates n trajectories from random starting points. Consider a parallel implementation of simulating n trajectories. Use Sobol sampling here.
