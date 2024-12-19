### Two differnet examples here:


- basic 3d rendering + textures with manual vertices


```
gcc  -o ./3d_example ./src/3d_example.c  -g -lm -lglfw -lGLEW -lGL
```

- Mesh Rendering


```
gcc -o ./mesh_renderer  ./src/mesh_renderer.c  -g -lm -lglfw -lGLEW -lGL
```