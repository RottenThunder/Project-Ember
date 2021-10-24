# DevLog - .../10/2021

## Day 1 (15/10/2021)
- Commit "First Commit - Entry Point"
    - The development of "Ember Engine" has begun
    - Added a way for the engine to create an application
    - Added an entry point for the whole program located in the "Ember.dll" file
- Commit "Logging Support"
    - Added logging support for the engine
    - Logging support was added with the help of a third-party library called "spdlog"
    - spdlog's library can be found [here](https://github.com/gabime/spdlog)

## Day 2 (16/10/2021)
- Commit "Added Premake"
    - Added the use of a build system (in this case, I used Premake)
    - Premake's library can be found [here](https://github.com/premake/premake-core)
    - Also, using the newly added build system, I made a Windows Batch File called "GenerateProjects.bat" which - if the user so desires - will make a Visual Studio 2019 Solution file for which you can view and edit the code
- Commit "Precompiled Headers"
    - Ember now uses precompiled headers
    - The precompiled header was named "empch.h"

## Day 5 (19/10/2021)
- Commit "OpenGL Window!!!"
    - Used OpenGL to create a cross-platform window to render graphics to
    - OpenGL's Library can be found [here](https://github.com/glfw/glfw)

## Day 8 (22/10/2021)
- Commit "Event System and Proper Window Class"
    - Created an Event System to handle events (such as the window resizing and whether a certain key on a keyboard is pressed)
    - Implemented a proper Window Class so making a window on different platforms shouldn't be too hard
    - Note: Events actually do not take effect, so the window does not close when the user presses the close button. A quick fix for this is to close the console window instead
- Commit "All Events are Dispatching!"
    - All Events are now dispatching, so the window actually closes now

## Day 9 (23/10/2021)
- Commit "Layer Implementation"
    - Added a way for the engine to create, destroy and store layers
    - All layers are stored on a layer stack which is a std::vector of layers

## Day 10 (24/10/2021)
- Commit "Modern OpenGL (Glad)"
    - Successfully implemented a way for the engine to access all of the modern OpenGL functions using a library called Glad
    - Glad's Library can be found [here](https://github.com/Dav1dde/glad)