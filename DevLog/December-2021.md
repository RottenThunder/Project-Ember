# DevLog - .../12/2021

## Day 52 (05/12/2021)
- Commit "Shader Asset Files"
    - I've added the functionality to make the shader code be read from a file
- Commit "Shader Library"
    - I've added a shader library system for the engine because some shaders can be reused for other objects
    
## Day 54 (07/12/2021)
- Commit "Game Dev - Constructing Maps"
    - Maps can now be read from a file and rendered on screen in the correct position
    - I am using a custom file extension for files with map data in it. I have named them ".level" files

## Day 55 (08/12/2021)
- Commit "Camera Controllers"
    - Added a Orthographic Camera Controller class to make controlling the camera a little bit more easier

## Day 58 (11/12/2021)
- Commit "Window Resizing, More Game Dev & General Maintenance"
    - The Engine now can change the viewport of the window whenever the window resizes
    - "Room1.level" was made and now the map is fully constructed with the correct tiles
    - Some general maintenance has been performed on minor parts of the engine

## Day 59 (12/12/2021)
- Commit "Renderer2D!!!"
    - The Renderer has now been re-enginneered to support more of a 2D-Style Renderer approach
    - An Example of this new approach is making a draw call a lot easier to use. All you have to do is call Ember::Renderer2D::DrawQuad() with the position, size and colour/texture of the Quad to be drawn
    - The Game code now has to be refactored to use the new Renderer2D

## Day 60 (13/12/2021)
- Commit "2 in 1 Shaders"
    - The Renderer now uses 1 Shader to render the shader and texture at the same time
    - This gives way to adding tints to textures
    - The Game Code has been refactored to use the new Renderer2D