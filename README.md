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

### Day 86 (08/01/2022)
- Commit "Game Development with the Batch Renderer"
    - The Game Scene is back, and now being rendered by the batch renderer
    - I have used all of the tiles from the game "The Legend of Zelda: A Link to the Past"

### Day 91 (13/01/2022)
- Commit "Redesigned Level File Reader"
    - The algorithm that read the ".level" files has been redesigned to be better

### Day 98 (20/01/2022)
- Commit "AABB Collisions"
    - The collision system got reworked to include AABB - Axis Aligned Bounding Boxes
    - I have also downloaded some tiles from [https://kenney.nl/](https://kenney.nl/), the exact sprites can be found here -> [https://kenney.nl/assets/rpg-base](https://kenney.nl/assets/rpg-base)