Вот пример README файла для проекта на GitHub:

---

# Drone Harvesting System

This project is a simulation of an **agricultural drone management system** based on the classic "Snake" game mechanics. The drones are responsible for harvesting pumpkins from the field, and the program supports both **manual control** and **autopilot** modes.

## Table of Contents
- [Project Description](#project-description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Screenshots](#screenshots)
- [Build Process](#build-process)
- [Contributing](#contributing)
- [License](#license)

## Project Description
This project simulates a system where drones move across a field to collect pumpkins. The player can control the drones manually or allow them to operate in autopilot mode, where they automatically find and collect the nearest pumpkins. The game is built using the **C programming language** and the **ncurses** library for terminal-based graphics.

## Features
- Manual and autopilot modes for drone control.
- Multiple drones collecting pumpkins in parallel (up to 5).
- Autopilot uses a simple nearest-pumpkin algorithm for efficient harvesting.
- Visual representation of drones and pumpkins in the terminal using the ncurses library.
- Real-time gameplay with collision detection and object interaction.

## Installation
To run this project, you need to have the `gcc` compiler and the `ncurses` library installed on your system. Use the following commands to install them on Ubuntu:

```bash
sudo apt-get update
sudo apt-get install gcc libncurses5-dev libncursesw5-dev
```

### Clone the Repository
Clone the project repository to your local machine:

```bash
git clone https://github.com/your-username/drone-harvesting-system.git
cd drone-harvesting-system
```

## Usage

### Compiling the Program

You can compile the program using the provided `Makefile`:

```bash
make
```

Alternatively, you can use the `run.sh` script to compile and run the program:

```bash
./run.sh
```

### Running the Program
After compiling, you can run the program by executing the `main` file:

```bash
./main
```

Upon running, you will be prompted to select a mode:
- Press `'a'` to select autopilot mode.
- Press `'m'` to select manual control mode.
- Press `'q'` to quit the game.

## Controls

- **Autopilot Mode**: The drone will automatically move towards the nearest pumpkin and collect it.
- **Manual Mode**: Use the arrow keys (`UP`, `DOWN`, `LEFT`, `RIGHT`) to control the drone's movement.
- **Quit Game**: Press `'q'` at any time to quit the game.

## Screenshots

### Initial Screen
The initial screen will prompt you to choose a mode:

![Initial screen](link-to-image)

### Autopilot Mode
In autopilot mode, drones automatically move and collect pumpkins:

![Autopilot mode](link-to-image)

### Manual Mode
In manual mode, the user controls the drones with the arrow keys:

![Manual mode](link-to-image)

## Build Process

This project uses the `Makefile` for building. Simply run the following command to compile the project:

```bash
make
```

To clean up the build files:

```bash
make clean
```

You can also use the `run.sh` script for a combined compile-and-run process:

```bash
./run.sh
```

## Contributing
Feel free to fork this repository, make improvements, and submit pull requests. Any contributions that improve functionality, fix bugs, or enhance documentation are welcome.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.
