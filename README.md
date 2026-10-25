# 🚢 Battleships Simulator

[![GitHub License](https://img.shields.io/github/license/ZephyrNULL/battleships-simulator?style=flat-square&color=blue)](LICENSE)
[![GitHub Commits](https://img.shields.io/github/commit-activity/w/ZephyrNULL/battleships-simulator?style=flat-square)](https://github.com/ZephyrNULL/battleships-simulator/commits/main)
[![GitHub Workflow Status](https://img.shields.io/badge/build-passing-success?style=flat-square)]()

A robust, console-based implementation of the classic **Battleships** game developed entirely in **C**. This project places a heavy emphasis on robust memory management, custom struct design, clean separation of UI/logic layers, and tactical physics calculations to deliver an engaging terminal simulation experience.

---

##  Table of Contents

- [About the Project](#-about-the-project)
- [Key Features](#-key-features)
- [Project Architecture & File Structure](#-project-architecture--file-structure)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Building and Running](#building-and-running)
- [Memory Management & Design Principles](#-memory-management--design-principles)
- [Contributing](#-contributing)
- [License](#-license)

---

##  About the Project

The **Battleships Simulator** moves beyond a standard grid-marking puzzle by incorporating tactical components, custom data structures, and rigorous memory tracking. Designed for developers and enthusiasts interested in systems programming, this application demonstrates how modular design, custom structures (`struct`), and header-source separation can be effectively applied in modern C programming.

---

##  Key Features

* **Custom Structs:** Implements tailored data structures representing various naval units, including specialized escort ships and heavy battleships.
* **Physics Engine Integration:** Features specialized range and impact functions (`physics.c`) to determine combat mechanics, distance metrics, and hit probabilities.
* **Modular UI Layers:** Separates core simulation logic from user interface handlers (`ui.c`, `part1_ui.c`, `part2_ui.c`) for cleaner code maintenance and flexibility.
* **Robust Memory Handling:** Employs strict allocation and deallocation protocols to prevent memory leaks during simulation loops and dynamic entity creation.

---

##  Project Architecture & File Structure

The project is structured into logical modules to separate physics calculations, game state structures, and user interface controls:

| File / Directory | Description |
| :--- | :--- |
| **`structures.h`** | Defines custom data types for battleships, escort ships, and game states. |
| **`physics.c` / `.h`** | Implements ballistic calculations, range detection, and impact logic. |
| **`ui.c` / `.h`** | Handles overarching simulation flow and terminal interface prompts. |
| **`part1.c` / `.h`** | Core logic implementation for Part 1, including iteration routines. |
| **`part1_ui.c` / `.h`** | User interface runner functions specific to Part 1. |
| **`part2_ui.h`** | Header configurations for Part 2 UI extensions. |
| **`LICENSE`** | MIT open-source license governing the repository. |

---

##  Getting Started

To get a local copy up and running on your machine, follow these simple steps.

### Prerequisites

Ensure you have a standard C compiler (such as `gcc` or `clang`) and `make` installed on your system.

```bash
# Verify gcc installation
gcc --version

# Verify make installation
make --version
