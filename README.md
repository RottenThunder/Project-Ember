# Project Ember [![License](https://img.shields.io/github/license/RottenThunder/Project-Ember.svg)](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

## About
Project Ember is an A-Level (Year 12) Computer Science Project that is focused on designing a game that is powered by a game engine. This game engine will be named after the project. Note that this project will only be targeting Windows for the time being, Multi-Platform support will be coming soon!!!

***

## Getting Started
<ins>**1. Downloading the repository**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/RottenThunder/Project-Ember`. This can be done by opening a command-prompt window (cmd.exe) and typing the relative command followed by a space and then the path in which to download the repository. The command should look lke this -> `git clone --recursive https://github.com/RottenThunder/Project-Ember repos\Project-Ember`.

<ins>**2. Generating the projects**</ins>

Run the [GenerateProjects.bat](https://github.com/RottenThunder/Project-Ember/blob/master/GenerateProjects.bat) File found at the root of the repository, you can edit the code from there.

## Recent Devlog Updates
(All DevLog Updates can be found in the [DevLog Folder](https://github.com/RottenThunder/Project-Ember/tree/master/DevLog))

### Day 9 (23/10/2021)
- Commit "Layer Implementation"
    - Added a way for the engine to create, destroy and store layers
    - All layers are stored on a layer stack which is a std::vector of layers

### Day 10 (24/10/2021)
- Commit "Modern OpenGL (Glad)"
    - Successfully implemented a way for the engine to access all of the modern OpenGL functions using a library called Glad
    - Glad's Library can be found [here](https://github.com/Dav1dde/glad)

### Day 13 (27/10/2021)
- Commit "Linux Support (Maybe)"
    - Added a way for the engine to make a window on linux. I have not tried it out on linux though
    - General quality of life changes