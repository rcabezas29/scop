# SCOP - GPU rendering with OpenGL

## 🎯 About

This project is a basic 3D rendering engine written in **C++** using **OpenGL**, **GLFW**, and **GLAD**. It loads and displays a 3D model from an `.obj` file and allows user interaction through keyboard inputs.

The program is designed to showcase a rotating 3D object (such as the 42 school logo), with smooth switching between flat-colored faces and a textured surface—no external libraries are used for object loading, matrix math, or shaders.

## 🧱 Technologies Used

- **C++**
- **OpenGL**
- **GLFW** – for window and input management
- **GLAD** – for loading OpenGL function pointers

## ✨ Features

- Load and parse `.obj` 3D model files
- Render models with:
  - Per-face color shading
  - Texturing with toggling via keypress (with smooth transition)
- Basic camera controls
- Model rotates around its center axis
- Custom shader compilation and management

## 🎮 Controls

| Key        | Action                               |
|------------|--------------------------------------|
| Mouse wheel| Zoom Camera                          |
| `T`        | Toggle between color and texture     |
| `ESC`      | Exit the program                     |

## 🧠 How Shaders Work (Simplified)

Shaders are small programs that run on the GPU to handle graphics rendering. In OpenGL, you typically use two types of shaders:

### 1. Vertex Shader
- Executes once per vertex
- Transforms 3D coordinates (model space) to 2D screen space
- Handles perspective projection and object rotation/translation

### 2. Fragment Shader
- Executes once per pixel
- Calculates the final color of a pixel
- Here, it decides whether to display a flat color per face or sample from a texture

In this project:
- Shaders are written in GLSL
- Loaded at runtime from custom files
- Compiled and linked manually using OpenGL functions
- Uniforms are used to pass transformation matrices and toggle states

### Build

```bash
make
./scop <path/to/model.obj>
```

## Examples

![](/assets/42.gif)
![](/assets/teapot.gif)
![](/assets/cow.gif)

## RESOURCES
- https://en.wikipedia.org/wiki/Wavefront_.obj_file
- https://github.com/ssloy/tinyrenderer/wiki
- https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
- https://www.glfw.org/documentation.html
- https://learnopengl.com/
