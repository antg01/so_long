/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:59:58 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 10:08:09 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to handle player movement based on key press.
 *
 * This function updates the player's position based on the keycode received.
 * It checks if the new position is valid and updates the game state accordingly.
 * It also handles the case for closing the window when
 * the escape key is pressed.
 *
 * Parameters:
 * - int keycode: The keycode of the pressed key.
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 */
void	handle_player_movement(int keycode, t_vars *vars)
{
	int	new_x;
	int	new_y;

	new_x = vars->map.player.pos.x;
	new_y = vars->map.player.pos.y;
	if (keycode == 65307 || keycode == 53)
		close_window(vars);
	else if (keycode == 119 || keycode == 65362 || keycode == 13
		|| keycode == 126)
		new_y -= 1;
	else if (keycode == 115 || keycode == 65364 || keycode == 1
		|| keycode == 125)
		new_y += 1;
	else if (keycode == 97 || keycode == 65361 || keycode == 0
		|| keycode == 123)
		new_x -= 1;
	else if (keycode == 100 || keycode == 65363 || keycode == 2
		|| keycode == 124)
		new_x += 1;
	if (is_valid_move(&vars->map, new_x, new_y))
	{
		key_count(keycode, vars);
		move_player(vars, new_x, new_y);
	}
	render_map(vars);
}

/*
 * Function to handle key press events.
 *
 * This function processes key press events to handle game logic. If the game
 * is over or won, pressing the specified key will close the window. Otherwise,
 * it handles player movement based on the key press.
 *
 * Parameters:
 * - int keycode: The keycode of the pressed key.
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 *
 * Return:
 * - int: Always returns 0.
 */
int	key_hook(int keycode, t_vars *vars)
{
	if (vars->game_over || vars->game_won)
	{
		if (keycode == 53)
			close_window(vars);
		return (0);
	}
	handle_player_movement(keycode, vars);
	return (0);
}

/*
 * Function to check if a move to a specified position is valid.
 *
 * This function determines if the player's move to a given position (x, y)
 * is within the boundaries of the game map and not blocked by a wall.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int x: The x-coordinate of the position to check.
 * - int y: The y-coordinate of the position to check.
 *
 * Return:
 * - bool: Returns true if the move is valid, otherwise returns false.
 */
int	is_valid_move(t_map *map, int x, int y)
{
	if (x >= map->width || y >= map->height)
	{
		return (FALSE);
	}
	if (map->grid[y][x] == WALL)
	{
		return (FALSE);
	}
	if (map->grid[y][x] == EXIT && map->collectibles_count)
	{
		return (FALSE);
	}
	return (TRUE);
}

/*
 * Function to move the player to a specified position.
 *
 * This function updates the player's position on the game map based on the
 * specified coordinates (x, y). It handles interactions with collectibles,
 * the exit, and enemies.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 * - int x: The x-coordinate of the new position.
 * - int y: The y-coordinate of the new position.
 */
void	move_player(t_vars *vars, int x, int y)
{
	t_map	*map;

	map = &vars->map;
	if (map->grid[y][x] == COLLECTIBLE)
	{
		map->collectibles_count--;
		map->grid[y][x] = EMPTY;
	}
	else if ((map->grid[y][x] == EXIT) && (map->collectibles_count == 0))
	{
		map->grid[map->player.pos.y][map->player.pos.x] = EMPTY;
		map->grid[y][x] = EXIT;
		map->player.pos.x = x;
		map->player.pos.y = y;
		vars->game_won = 1;
		return ;
	}
	else if (map->grid[y][x] == ENEMY)
	{
		vars->game_over = 1;
		return ;
	}
	move_player_update(map, x, y);
}

/*
 * Function to handle closing the game window.
 *
 * This function prints a message indicating the window is closed, destroys
 * the MLX window, frees the allocated memory for the game map,
 * and exits the program.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 *
 * Return:
 * - int: Always returns 0.
 */
int	close_window(t_vars *vars)
{
	ft_printf("Window closed. Exiting...\n");
	mlx_destroy_window(vars->mlx, vars->win);
	free_map(vars, &vars->map);
	exit(0);
	return (0);
}
