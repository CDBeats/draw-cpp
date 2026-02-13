# Draw-C++

This project is a C++ rewrite of the original Python-based [`draw.py`](draw.py). The primary goal of this rewrite is to improve performance and scalability, making the project more suitable for larger and more complex use cases.

## Overview

The original `draw.py` project was a Python-based application designed for [brief description of what `draw.py` does, e.g., "creating 2D graphics and animations"]. While Python provided a great starting point, the need for better performance and scalability led to the decision to rewrite the project in C++.

This C++ version leverages the power of the [raylib](external/raylib/README.md) library, a simple and easy-to-use library for game development and graphics programming. By using C++, the project benefits from faster execution times, better memory management, and improved modularity for future development.

## Features

- **Improved Performance**: The C++ implementation is optimized for speed and efficiency, making it suitable for more demanding applications.
- **Scalability**: The project is designed with modularity in mind, allowing for easier expansion and maintenance.
- **Integration with raylib**: Utilizes the raylib library for rendering and graphics, providing a robust foundation for 2D and 3D graphics.
- **Feature Parity with `draw.py`**: All features from the original Python project are implemented, with additional improvements and optimizations.

## Project Structure

```
.gitignore
CMakeLists.txt
draw.py
LICENSE
README.md
.vscode/
    settings.json
assets/
external/
    raylib/
        ...
include/
    Background.hpp
    Constants.hpp
    Game.hpp
    Obstacles.hpp
src/
    Background.cpp
    Game.cpp
    main.cpp
    Obstacles.cpp
```

- **`draw.py`**: The original Python implementation.
- **`src/`**: Contains the C++ source code files.
- **`include/`**: Header files for the C++ implementation.
- **`external/raylib/`**: The raylib library used for rendering and graphics.
- **`assets/`**: Resources such as images, textures, and other assets used in the project.
- **`.vscode/`**: Configuration files for Visual Studio Code.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++17 or later.
- [CMake](https://cmake.org/) for building the project.
- [raylib](https://www.raylib.com/) library (already included in the `external/` directory).

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/draw-cpp.git
   cd draw-cpp
   ```

2. Create a build directory and navigate to it:
   ```bash
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   cmake --build .
   ```

5. Run the executable:
   ```bash
   ./draw-cpp
   ```

## Usage

[Provide instructions on how to use the application, including any command-line arguments or configuration options.]

## Contributing

Contributions are welcome! If you'd like to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes.
4. Push your branch and create a pull request.

## License

This project is licensed under the [LICENSE](LICENSE) file.

## Acknowledgments

- [raylib](https://www.raylib.com/) for providing a simple and powerful graphics library.
- The original `draw.py` project for inspiring this rewrite.
