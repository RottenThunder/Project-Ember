# Project Ember [![License](https://img.shields.io/github/license/RottenThunder/Project-Ember.svg)](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

## About
Project Ember is an A-Level (Year 12) Computer Science Project that is focused on designing a game that is powered by a game engine. This game engine will be named after the project. Note that this project will only be targeting Windows for the time being.

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

### Day 29 (12/11/2021)
- Commit "ImGui and Pathfinding"
    - The Enemy now uses a pathfinding algorithm to find the optimal route to the player (tracking him)
    - ImGui has been successfully implemented and has been hooked up the event system, meaning that the UI windows ImGui creates can be moved and be intercated with

### Day 31 (14/11/2021)
- Commit "Shader Abstraction"
    - Shaders are being abstracted, aswell as uniforms can now be changed dynamically

### Day 32 (15/11/2021)
- Commit "ImGui Docking"
    - ImGui now has the ability to dock any ui window it creates inside of the window
    - Any Layer can now have access to ImGui Renderering