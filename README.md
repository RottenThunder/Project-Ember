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

### Day 2 (16/10/2021)
- Commit "Precompiled Headers"
    - Ember now uses precompiled headers
    - The precompiled header was named "empch.h"

### Day 5 (19/10/2021)
- Commit "OpenGL Window!!!"
    - Used OpenGL to create a cross-platform window to render graphics to
    - OpenGL's Library can be found [here](https://github.com/glfw/glfw)

### Day 8 (22/10/2021)
- Commit "Event System and Proper Window Class"
    - Created an Event System to handle events (such as the window resizing and whether a certain key on a keyboard is pressed)
    - Implemented a proper Window Class so making a window on different platforms shouldn't be too hard
    - Note: Events actually do not take effect, so the window does not close when the user presses the close button. A quick fix for this is to close the console window instead