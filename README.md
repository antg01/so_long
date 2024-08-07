# so_long

## About
This project is a simple 2D game written in C. The objective is to navigate through a map, collect items, and reach the exit. The game uses the MiniLibX library for graphical rendering.

## Folder Structure

- **assets**: Contains graphical assets used in the game.
- **ft_printf**: Custom implementation of the printf function.
- **gnl**: Implementation of the get_next_line function.
- **includes**: Header files for the project.
- **maps**: Contains map files defining the levels.
- **mlx**: MiniLibX library files.
- **src**: Source code of the game.

## Getting Started

### Prerequisites
- Make
- GCC
- MiniLibX library

### Installation

Clone the repository:
```bash
git clone https://github.com/antg01/so_long.git
cd so_long
```

Compile the project:
```bash
make
```

### Usage

Run the game:
```bash
./so_long path/to/map.ber
```

### Controls
- **W**: Move up
- **A**: Move left
- **S**: Move down
- **D**: Move right

### Maps

You can create custom maps by placing `.ber` files in the `maps` directory. Each map file should adhere to the required format.


## Acknowledgments

- MiniLibX library for graphical rendering
- 42 Network for the project inspiration
