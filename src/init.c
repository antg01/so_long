/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:33:58 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 09:51:15 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to initialize the game map and game variables.
 *
 * This function sets the initial values for the map structure and the game
 * variables in the vars structure. It ensures all pointers are set to NULL
 * and numerical values are initialized to zero or appropriate default values.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 * - t_map *map: Pointer to the map structure containing the game grid & images.
 */
void	init_map(t_vars *vars, t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles_count = 0;
	map->wall_img = NULL;
	map->player_img = NULL;
	map->enemy_img = NULL;
	map->collectible_img = NULL;
	map->exit_img = NULL;
	map->empty_img = NULL;
	map->player.pos.x = -1;
	map->player.pos.y = -1;
	vars->moves = 0;
	vars->game_over = 0;
	vars->game_won = 0;
	map->player.sprite.img = NULL;
}

/*
 * Function to initialize the game environment.
 *
 * This function initializes the MLX library & creates a new window for the game.
 * It sets up the necessary graphical environment for the game to run.
 * If initialization fails at any point, it prints an error message
 * and returns false.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 * - t_map *map: Pointer to the map structure containing
 * the game grid and dimensions.
 *
 * Return:
 * - bool: Returns true if the game environment is successfully initialized,
 * otherwise returns false.
 */
int	init_game(t_vars *vars, t_map *map)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_printf("Error: Failed to initialize mlx\n");
		return (FALSE);
	}
	vars->win = mlx_new_window(vars->mlx, map->width * TILE_SIZE, map->height
			* TILE_SIZE, WIN_NAME);
	if (!vars->win)
	{
		ft_printf("Error: Failed to create window\n");
		return (FALSE);
	}
	return (TRUE);
}

/*
 * Function to load images for the game map.
 *
 * This function checks for the existence of image files and then loads them
 * using the MLX library. If any image fails to load, an error message
 * is printed.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 * - t_map *map: Pointer to map structure containing the game grid & images.
 * - int *img_width: Pointer to store the width of the loaded images.
 * - int *img_height: Pointer to store the height of the loaded images.
 */
void	load_images(t_vars *vars, t_map *map, int *img_width, int *img_height)
{
	check_file_exists("assets/walls/other_1.xpm");
	check_file_exists("assets/hero/fly1.xpm");
	check_file_exists("assets/enemy/spider.xpm");
	check_file_exists("assets/collectible/poop.xpm");
	check_file_exists("assets/gate/gate_3.xpm");
	check_file_exists("assets/walls/other_0.xpm");
	map->wall_img = mlx_xpm_file_to_image(vars->mlx, "assets/walls/other_1.xpm",
			img_width, img_height);
	map->player_img = mlx_xpm_file_to_image(vars->mlx, "assets/hero/fly1.xpm",
			img_width, img_height);
	map->enemy_img = mlx_xpm_file_to_image(vars->mlx, "assets/enemy/spider.xpm",
			img_width, img_height);
	map->collectible_img = mlx_xpm_file_to_image(vars->mlx,
			"assets/collectible/poop.xpm", img_width, img_height);
	map->exit_img = mlx_xpm_file_to_image(vars->mlx, "assets/gate/gate_3.xpm",
			img_width, img_height);
	map->empty_img = mlx_xpm_file_to_image(vars->mlx,
			"assets/walls/other_0.xpm", img_width, img_height);
	if (!map->wall_img || !map->player_img || !map->enemy_img
		|| !map->collectible_img || !map->exit_img || !map->empty_img)
		ft_printf("Error: Failed to load one or more images\n");
}

/*
 * Function to free the allocated memory for the game map and destroy images.
 *
 * This function frees the memory allocated for the game map grid and destroys
 * all loaded images using the MLX library. It ensures that all resources are
 * properly released.
 *
 * Parameters:
 * - t_vars *vars: Pointer to vars structure containing game variables.
 * - t_map *map: Pointer to the map structure containing the game grid & images.
 */
void	free_map(t_vars *vars, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	if (map->wall_img)
		mlx_destroy_image(vars->mlx, map->wall_img);
	if (map->player.sprite.img)
		mlx_destroy_image(vars->mlx, map->player.sprite.img);
	if (map->enemy_img)
		mlx_destroy_image(vars->mlx, map->enemy_img);
	if (map->collectible_img)
		mlx_destroy_image(vars->mlx, map->collectible_img);
	if (map->exit_img)
		mlx_destroy_image(vars->mlx, map->exit_img);
	if (map->empty_img)
		mlx_destroy_image(vars->mlx, map->empty_img);
}

/*
 * Function to print an error message and exit the program.
 *
 * This function prints the provided error message to the standard error output
 * and then terminates the program with a failure status.
 *
 * Parameters:
 * - char *message: Pointer to the string containing the error message
 * to be printed.
 */
void	error_exit(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
