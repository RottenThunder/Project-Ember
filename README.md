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

### Day 60 (13/12/2021)
- Commit "2 in 1 Shaders"
    - The Renderer now uses 1 Shader to render the shader and texture at the same time
    - This gives way to adding tints to textures
    - The Game Code has been refactored to use the new Renderer2D

### Day 62 (15/12/2021)
- Commit "Profiling & More Game Dev"
    - Profiling capabilities have now been added to the engine
    - The results of the profiling session is stored in a .json file, which then can be viewed by a web browser
    - Tilemaps now have collisions attached to them

### Day 63 (16/12/2021)
- Commit "Instrumentation & Improved 2D Rendering API"
    - Improved Profiling and Improved 2D Rendering API has been implemented to the engine
    - The engine can now draw rotated quads