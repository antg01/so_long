/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:34:36 by angerard          #+#    #+#             */
/*   Updated: 2024/08/06 17:24:30 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to render the game map.
 *
 * This function renders each tile of the game map by iterating through the grid.
 * It also renders the number of moves and, if the game is over or won, displays
 * the end game screen.
 *
 * Parameters:
 * - t_vars *vars: Pointer to vars struct containing game variables & map data.
 */
void	render_map(t_vars *vars)
{
	int	y;
	int	x;

	if (vars->map.height <= 0 || vars->map.width <= 0)
	{
		ft_printf("Error: Invalid map dimensions\n");
		return ;
	}
	y = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (x < vars->map.width)
		{
			render_tile(vars, x, y);
			x++;
		}
		y++;
	}
	render_moves(vars);
	if (vars->game_over || vars->game_won)
	{
		render_end_game(vars);
	}
}

/*
 * Function to render a single tile on the game window.
 *
 * This function determines the correct image for a tile based on the map grid
 * and renders it at the specified position (x, y). It checks for null values
 * and prints error messages if necessary.
 *
 * Parameters:
 * - t_vars *vars: Pointer to vars struc containing game variables & map data.
 * - int x: The x-coordinate of the tile in the map grid.
 * - int y: The y-coordinate of the tile in the map grid.
 */
void	render_tile(t_vars *vars, int x, int y)
{
	void	*img;

	if (vars->map.grid == NULL || vars->map.grid[y] == NULL)
	{
		ft_printf("Error: Null map grid\n");
		return ;
	}
	img = get_tile_image(vars, vars->map.grid[y][x]);
	if (!img)
	{
		ft_printf("Error: Null image for tile at (%d, %d)\n", x, y);
		return ;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
}

/*
 * Function to get the image corresponding to a tile character.
 *
 * This function returns the appropriate image for a given tile character
 * based on the type of the tile (WALL, PLAYER, ENEMY, COLLECTIBLE, EXIT).
 * If the tile character does not match any of these,
 * it returns the empty tile image.
 *
 * Parameters:
 * - t_vars *vars: Pointer to vars struct containing game variables & map images.
 * - char tile: The character representing the type of tile.
 *
 * Return:
 * - void*: Pointer to the image corresponding to the tile character.
 */
void	*get_tile_image(t_vars *vars, char tile)
{
	if (tile == WALL)
		return (vars->map.wall_img);
	if (tile == PLAYER)
		return (vars->map.player_img);
	if (tile == ENEMY)
		return (vars->map.enemy_img);
	if (tile == COLLECTIBLE)
		return (vars->map.collectible_img);
	if (tile == EXIT)
		return (vars->map.exit_img);
	return (vars->map.empty_img);
}
