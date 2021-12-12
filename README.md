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

### Day 55 (08/12/2021)
- Commit "Camera Controllers"
    - Added a Orthographic Camera Controller class to make controlling the camera a little bit more easier

### Day 58 (11/12/2021)
- Commit "Window Resizing, More Game Dev & General Maintenance"
    - The Engine now can change the viewport of the window whenever the window resizes
    - "Room1.level" was made and now the map is fully constructed with the correct tiles
    - Some general maintenance has been performed on minor parts of the engine

### Day 59 (12/12/2021)
- Commit "Renderer2D!!!"
    - The Renderer has now been re-enginneered to support more of a 2D-Style Renderer approach
    - An Example of this new approach is making a draw call a lot easier to use. All you have to do is call Ember::Renderer2D::DrawQuad() with the position, size and colour/texture of the Quad to be drawn
    - The Game code now has to be refactored to use the new Renderer2D