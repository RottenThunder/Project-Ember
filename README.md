# Project Ember [![License](https://img.shields.io/github/license/RottenThunder/Project-Ember.svg)](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

## About
Project Ember is an A-Level (Year 12) Computer Science Project that is focused on designing a game that is powered by a game engine. This game engine will be named after the project. Note that this project will only be targeting Windows for the time being, Multi-Platform support will be coming soon!!!

## Licensing
[BSD 3-Clause License](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

***

## Getting Started
<ins>**1. Downloading the repository**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/RottenThunder/Project-Ember`. This can be done by opening a command-prompt window (cmd.exe) and typing the relative command followed by a space and then the path in which to download the repository. The command should look lke this -> `git clone --recursive https://github.com/RottenThunder/Project-Ember repos\Project-Ember`.

<ins>**2. Generating the projects**</ins>

Run the [GenerateProjects.bat](https://github.com/RottenThunder/Project-Ember/blob/master/GenerateProjects.bat) File found at the root of the repository, you can edit the code from there.

## Recent Devlog Updates
(All DevLog Updates can be found in the [DevLog Folder](https://github.com/RottenThunder/Project-Ember/tree/master/DevLog))

### Day 24 (07/11/2021)
- Commit "Delta Time"
    - The engine now calculates and can provide Delta Time for people using the engine
- Commit "Orthographic Camera"
    - The Engine can now create an orthographic camera and the camera can be moved freely

## Day 26 (09/11/2021)
- Commit "Transforms"
    - Every object rendered in the game engine now has a transform, which means the object can be moved
    - Game Dev is going good, The player (Red Rectangle) can be moved by keyboard input on a grid-like system. Also a blue rectangle is being rendered, which is going to be an enemy, but no logic is being put on him