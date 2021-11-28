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

## Day 31 (14/11/2021)
- Commit "Shader Abstraction"
    - Shaders are being abstracted, aswell as uniforms can now be changed dynamically

## Day 32 (15/11/2021)
- Commit "ImGui Docking"
    - ImGui now has the ability to dock any ui window it creates inside of the window
    - Any Layer can now have access to ImGui Renderering

## Day 35 (18/11/2021)
- Commit "Ref Counting"
    - The engine now has a Reference Counting system for std::shared_ptr and std::unique_ptr

## Day 38 (21/11/2021)
- Commit "Textures & Blending"
    - The engine can now render textures
    - Textures with the Alpha channel are also supported (for example: .png)

## Day 41 (24/11/2021)
- Commit "Game Dev - Starting a Collision System"
    - I've been experimenting how to make a basic Collision System and had no luck yet
    - Entities collide but unfortunately the way in which it blocks movement is not working correctly

## Day 45 (28/11/2021)
- Commit "Game Dev - Mostly Finished Collision System"
    - I've managed to mostly finish the collision system for the game
    - There is still a few more tweaks that i still need to do