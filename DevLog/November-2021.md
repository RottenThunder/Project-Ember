# DevLog - .../11/2021

## Day 23 (06/11/2021)
- Commit "Game Dev - Grid System"
    - I have started using the engine to create a game
    - The basic idea for the game is for it to be a 2D grid-based game
    - The grid sytem has been successfully implemented
- Commit "Game Dev - Moving Player"
    - A Red Rectangle is drawn and acts as the player
    - The player can move with WASD or Arrow Keys, in terms of the new grid system

## Day 24 (07/11/2021)
- Commit "Delta Time"
    - The engine now calculates and can provide Delta Time for people using the engine
- Commit "Orthographic Camera"
    - The Engine can now create an orthographic camera and the camera can be moved freely

## Day 26 (09/11/2021)
- Commit "Transforms"
    - Every object rendered in the game engine now has a transform, which means the object can be moved
    - Game Dev is going good, The player (Red Rectangle) can be moved by keyboard input on a grid-like system. Also a blue rectangle is being rendered, which is going to be an enemy, but no logic is being put on him

## Day 28 (11/11/2021)
- Commit "Game Dev - Camera Zoom"
    - The camera is now able to be moved by keyboard input
    - The camera can now zoom in and out
    - The enemy (Blue square) is now moving

## Day 29 (12/11/2021)
- Commit "ImGui and Pathfinding"
    - The Enemy now uses a pathfinding algorithm to find the optimal route to the player (tracking him)
    - ImGui has been successfully implemented and has been hooked up the event system, meaning that the UI windows ImGui creates can be moved and be intercated with