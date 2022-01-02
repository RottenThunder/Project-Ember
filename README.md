# Project Ember [![License](https://img.shields.io/github/license/RottenThunder/Project-Ember.svg)](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

## About
Project Ember is an A-Level (Year 12) Computer Science Project that is focused on designing a game that is powered by a game engine. This game engine will be named after the project. Note that this project will only be targeting Windows for the time being.

## Licensing
[BSD 3-Clause License](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

***

## Getting Started
<ins>**1. Downloading the repository**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/RottenThunder/Project-Ember`. This can be done by opening a command-prompt window (cmd.exe) and typing the relative command followed by a space and then the path in which to download the repository. The command should look lke this -> `git clone --recursive https://github.com/RottenThunder/Project-Ember repos\Project-Ember`.

<ins>**2. Fixing the Issues**</ins>

Next, you need to go in to the [Fixed_Files Folder](https://github.com/RottenThunder/Project-Ember/tree/master/Fixed_Files) and copy the "premake5.lua" file in to this path -> `Ember/vendor/imgui`, you need to replace this file with the one that is already there.

<ins>**3. Generating the projects**</ins>

Run the [GenerateProjects.bat](https://github.com/RottenThunder/Project-Ember/blob/master/GenerateProjects.bat) File found at the root of the repository, you can edit the code from there.

## Recent Devlog Updates
(All DevLog Updates can be found in the [DevLog Folder](https://github.com/RottenThunder/Project-Ember/tree/master/DevLog))

### Day 75 (28/12/2021)
- Commit "Batch Rendering Textures"
    - The Engine can now batch render textures together
    - There is a wierd error that occurs when the program deletes textures, it does not seem to be fatal

### Day 79 (01/01/2022)
- Commit "Batch Rendering Rotation"
    - The Engine can now batch render rotated quads

### Day 80 (02/01/2022)
- Commit "Stats for the Batch Renderer"
    - I've added some statistics for the batch renderer, so i can see how how many draw calls it takes to render a certain scene