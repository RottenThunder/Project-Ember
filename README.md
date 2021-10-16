# Project Ember [![License](https://img.shields.io/github/license/RottenThunder/Project-Ember.svg)](https://github.com/RottenThunder/Project-Ember/blob/master/LICENSE)

## About
Project Ember is an A-Level (Year 12) Computer Science Project that is focused on designing a game that is powered by a game engine. This game engine will be named after the project. Note that this project will only be targeting Windows.

***

## Getting Started
<ins>**1. Downloading the repository**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/RottenThunder/Project-Ember`. This can be done by opening a command-prompt window (cmd.exe) and typing the relative command followed by a space and then the path in which to download the repository. The command should look lke this -> `git clone --recursive https://github.com/RottenThunder/Project-Ember repos\Project-Ember`.

<ins>**2. Generating the projects**</ins>

Run the [GenerateProjects.bat](https://github.com/RottenThunder/Project-Ember/blob/master/GenerateProjects.bat) File found at the root of the repository, you can edit the code from there.

## Recent Devlog Updates
(All DevLog Updates can be found in the [DevLog Folder](https://github.com/RottenThunder/Project-Ember/tree/master/DevLog))
### Day 1 (15/10/2021)
- Commit "Logging Support"
    - Added logging support for the engine
    - Logging support was added with the help of a third-party library called "spdlog"
    - spdlog's library can be found [here](https://github.com/gabime/spdlog)

### Day 2 (16/10/2021)
- Commit "Added Premake"
    - Added the use of a build system (in this case, I used Premake)
    - Premake's library can be found [here](https://github.com/premake/premake-core)
    - Also, using the newly added build system, I made a Windows Batch File called "GenerateProjects.bat" which - if the user so desires - will make a Visual Studio 2019 Solution file for which you can view and edit the code
- Commit "Precompiled Headers"
    - Ember now uses precompiled headers
    - The precompiled header was named "empch.h"