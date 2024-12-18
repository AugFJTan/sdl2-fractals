# SDL2 Fractals

C++ implementation of various fractals with SDL2.

Available fractals:

1. Sierpinski triangle
2. Sierpinski carpet
3. Sierpinski curve
4. Fractal tree
   - Line version
   - Shape version
5. Koch snowflake
   - Line version
   - Shape version
6. Mandelbrot set
7. Julia set
8. Box fractal
9. Dragon curve
10. Barnsley fern
11. Gosper island

## Building

### Command Line

```sh
mkdir build
cd build
cmake -DSDL2_LIB=/path/to/SDL2/<target>/lib -DSDL2_INCLUDE=/path/to/SDL2/<target>/include ..
cmake --build .
```

### VS Code with CMake extension

In `settings.json`:

```json
{
    "cmake.configureSettings": {
        "SDL2_LIB": "/path/to/SDL2/<target>/lib",
        "SDL2_INCLUDE": "/path/to/SDL2/<target>/include"
    }
}
```

## Usage

On Windows, copy `SDL2.dll` into the same directory (i.e. `build`) as `main.exe`.

When running the executable, click on the window to cycle through each fractal.
