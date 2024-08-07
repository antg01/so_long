/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:42:00 by angerard          #+#    #+#             */
/*   Updated: 2024/08/06 11:04:19 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to check for duplicate players on the game map.
 *
 * This function iterates through the game map grid to count the number of player
 * characters ('P'). If the count is not exactly one, it prints an error message
 * and terminates the program.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int rows: Number of rows in the game grid.
 * - int cols: Number of columns in the game grid.
 */
void	check_player_duplicates(t_map *map, int rows, int cols)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map->grid[i][j] == PLAYER)
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		ft_printf("Error: There should be exactly one player 'P' in the map\n");
		exit(1);
	}
}

/*
 * Function to check for duplicate exits on the game map.
 *
 * This function iterates through the game map grid to count the number of exit
 * characters ('E'). If the count is not exactly one, it prints an error message
 * and terminates the program.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int rows: Number of rows in the game grid.
 * - int cols: Number of columns in the game grid.
 */
void	check_exit_duplicates(t_map *map, int rows, int cols)
{
	int	exit_count;
	int	i;
	int	j;

	exit_count = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map->grid[i][j] == EXIT)
				exit_count++;
			j++;
		}
		i++;
	}
	if (exit_count != 1)
	{
		ft_printf("Error: There should be exactly one exit 'E' in the map\n");
		exit(1);
	}
}

/*
 * Function to check if the map borders are properly closed by walls.
 *
 * This function verifies that the borders of the game map are enclosed
 * by walls ('W'). It checks the top, bottom, left, and right borders of the map.
 * If any border is not properly closed, it prints an error message and
 * terminates the program.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 */
void	check_map_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != WALL || map->grid[map->height - 1][i] != WALL)
		{
			ft_printf("Error: Map not closed by walls (top/bottom)\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != WALL || map->grid[i][map->width - 1] != WALL)
		{
			ft_printf("Error: Map not closed by walls  (left/right)\n");
			exit(1);
		}
		i++;
	}
	ft_printf("Map borders are properly closed by walls.\n");
}

/*
 * Function to check for errors in the game map.
 */
void	map_error_checker(t_map *map, int rows, int cols)
{
	check_player_duplicates(map, rows, cols);
	check_exit_duplicates(map, rows, cols);
	check_map_borders(map);
	check_valid_path(map);
	ft_printf("No error found in the map.\n");
}
