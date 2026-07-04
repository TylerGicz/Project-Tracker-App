Project Tracker: A Rosetta Stone for Application Development

In a world with endless means for application development, it can be difficult for an aspiring programmer to know which languages, frameworks, and tools are best for the job.

This repository acts as a live directory of demos to compare different technologies side-by-side. I am achieving this by building the exact same Project Tracker Application using as many different language stacks and tooling combinations as possible.

The Implementations

Each directory contains a fully functional version of the application built from scratch:

1.  Web Stack: JavaScript + HTML + CSS (Representing modern interpreted web paradigms)
2.  Native Desktop: C + Windows API (Win32) (Representing bare-metal, event-driven procedural native code)

Application Core Features

Every demo implements a uniform specification:

*   Interactive Project List: View, add, and dynamically edit distinct project modules.
*   Granular Project Descriptions: Contextual markdown-style descriptions unique to each project.
*   Scoped To-Do Lists: Local, editable task management lists nested specifically inside each project tracking block.
*   Global Aggregate Dashboard: A centralized, view-only roll-up showing all pending tasks globally.
*   Modular Application Message System: A custom UI notification stack/queue designed to handle warnings and error logging gracefully.

Getting Started

1. Web Version

Simply clone the repository and launch the application directly in any modern browser:

bash

    cd web
    # Open index.html in your browser

2. C + Win32 Native Version

Compiled targeting Windows environments using GCC/MinGW via a custom structured Makefile:

bash

    cd win32
    # Clean previous builds and compile
    mingw32-make clean
    mingw32-make
    
    # Run the native application
    ./app.exe