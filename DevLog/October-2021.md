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