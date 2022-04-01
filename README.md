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

### Day 113 (04/02/2022)
- Commit "Inventory System"
    - The game now has an inventory system which can be seen by pressing "I"
    - The Player is now a seperate class of it's own to accomadate the inventory being specific to only the player

### Day 164 (27/03/2022)
- Commit "So a lot has happened..."
    - Inventory system has been deleted
    - New game ideas were made (such as having cards in the game)
    - New pixel art has been made
    - The player has a way of attacking through the form of firing a projectile
    - Other minor performance upgrades have been implemented
    - And finally, i am so sorry for not updating the repository for a long time

### Day 169 (01/04/2022)
- Commit "Enemy Health Bars"
    - Made an algorithm to randomly place enemies in world space
    - Made a simple health bar system similar to the elder scrolls series