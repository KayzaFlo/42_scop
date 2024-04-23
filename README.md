# scop
scop is a 42's specialization project that introduce us to OpenGL and 3D visualization.<br>

<p align="center">
  <img src="/screenshots/teapot.gif" width="49%" />
  <img src="/screenshots/suzanne_normal.png" width="49%" />
</p>
<p align="center">
  <img src="/screenshots/42.png" width="32%" />
  <img src="/screenshots/suzanne_grid.png" width="32%" />
  <img src="/screenshots/backpack.png" width="32%" />
</p>

## Description

Scop is a .obj/.mtl file visualizer in [C++](https://cplusplus.com/doc/tutorial/) and [OpenGL](https://www.opengl.org/) with a few option to change shaders and move in the scene.<br>
I also use:<br>
	- [GLAD](https://github.com/Dav1dde/glad) to load Opengl methods<br>
	- [GLFW](https://www.glfw.org/) to manage the windows and input<br>
	- [STB](https://github.com/nothings/stb) to load texture images<br>

## Installation

##### Prerequisites:
[GLFW](https://www.glfw.org/) should be included as static lib, but if needed:<br>
Install on .brew: https://formulae.brew.sh/formula/glfw<br>

```bash
git clone git@github.com:KayzaFlo/42_scop.git
make
```

## Features

- camera movement with mouse and keyboard
- 3D model display using GPU through OpenGL
- no use of GLM, basics of Vector2/3/4 and Matrix recreated from scratch
- no 3D file importer, parsing and import of obj and mtl recreated from scratch (not a duplicate of Assimp, so some case might not be implemented)
- a few fragment and vertex shaders are available for tests


## Usage

```
    ./scop [.obj file] [.bmp texture]
```
[ESC][Q] - Exit<br>
[Mouse Click] : Camera Rotation<br>
[LeftCtrl, Space, W, A, S, D] Camera movement<br>
[F] Cycle Shaders<br>

## License

[MIT](https://choosealicense.com/licenses/mit/)
