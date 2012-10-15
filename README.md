cmd gui twin app
================

A simple demo on a cmd and gui twin app with the same function

> *[Github Project Page](https://github.com/quxiaofeng/cmd_gui_twin_app)*    

This application is based on Qt 4.8.1 and OpenCV 2.4.2 on msvc2010 32bit platform.

## Structure

### algorithms

Contains the common classes which are used by both CMD and GUI applications.
In my example, it is the image processing algorithms.

### cmd

The cmd option parser goes here.
This is optimized for batch process.
Assume the receive the input as both command line and text.

### gui

Provides oppotunities to revise and adjust parameters.

## Example

+ The cmd app reveives both one parameter and two parameters. One parameter for only input image file and output with suffix "_roc" and same filetype. Tow parameters specifies both input image filename and output image filename.

+ The gui takes no parameters and opens images through a open dialog.

### TODO

1. Try to find a industrial option parser for the cmd app.
2. Parse txt file in the cmd app.


### Notes

1. Parameters are public to avoid getters and setters.
2. Add further image process code.
