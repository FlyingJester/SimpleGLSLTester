SimpleGLSLTester
================

This program tests if a vertex and fragment shader compile and returns the errors if they don't. Just a GLSL syntax tester, really.

It loads a fragment shader, as the file frag.fs, and a vertex shader, as the file vert.vs. It compiles both, prints any errors 
encountered, attaches both to a GLSL program, prints any errors, and then links the program printing any errors. Then it quits. 

A test scene would be a nice addition.

Only works if you have X11, I'm afraid. Win32 version planned soon. I don't want to include SDL or SMFL or anything else to handle 
context creation just to do this.
