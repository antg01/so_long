/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:54:01 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 13:02:02 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Depth-First Search (DFS) to collect all collectibles on the game map.
 *
 * This function performs a depth-first search on the game map to find and
 * collect all collectibles. It marks visited cells and updates the count
 * of remaining collectibles. The search explores all four possible movements
 * (up, down, left, right) recursively until all collectibles are collected
 * or no valid path is found.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int **visited: 2D array tracking visited cells on the grid.
 * - t_point pos: Current position on the grid represented as a point (x, y).
 * - int *collected: Pointer to the count of remaining "C" to be collected.
 *
 * Returns:
 * - int: Returns TRUE, FALSE if no path exists.
 */
int	dfs_collectibles(t_map *map, int **visited, t_point pos, int *collected)
{
	int		movements[4][2];
	int		i;
	t_point	new_pos;

	init_movements(movements);
	if (map->grid[pos.y][pos.x] == COLLECTIBLE)
		(*collected)--;
	visited[pos.y][pos.x] = TRUE;
	if (*collected == 0)
		return (TRUE);
	i = 0;
	while (i < 4)
	{
		update_position(&pos, &new_pos, (int *)movements, i);
		if (is_valid_position(map, new_pos.x, new_pos.y)
			&& !visited[new_pos.y][new_pos.x])
		{
			if (dfs_collectibles(map, visited, new_pos, collected))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/*
 * Function to perform a Depth-First Search (DFS) to find an exit.
 *
 * This function uses DFS to traverse the game map starting from
 * a given position (pos). It marks positions as visited and
 * returns true if an exit is found.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - bool **visited: 2D array to keep track of visited positions.
 * - t_point pos: The starting position for the DFS traversal.
 *
 * Return:
 * - bool: Returns true if an exit is found, otherwise returns false.
 */
int	dfs_exit(t_map *map, int **visited, t_point pos)
{
	int		movements[4][2];
	int		i;
	t_point	new_pos;

	init_movements(movements);
	if (check_exit(map, pos.x, pos.y))
		return (TRUE);
	visited[pos.y][pos.x] = TRUE;
	i = 0;
	while (i < 4)
	{
		update_position(&pos, &new_pos, (int *)movements, i);
		if (is_valid_position(map, new_pos.x, new_pos.y)
			&& !visited[new_pos.y][new_pos.x])
		{
			if (dfs_exit(map, visited, new_pos))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/*
 * Function to check if a valid path exists from player to all items and exit.
 *
 * This function initializes the visited array, counts the collectibles,
 * and uses DFS to check if all collectibles can be collected and
 * if a path exists from the player's starting position to an exit.
 * If any check fails, it prints an error message and exits.
 *
 * Parameters:
 * - t_map *map: Pointer to map struct containing the game grid and player pos.
 *
 * Return:
 * - bool: Returns true if a valid path exists, otherwise exits the program.
 */
int	check_valid_path(t_map *map)
{
	t_point	start_pos;
	int		**visited;
	int		collected;

	visited = initialize_visited(map->height, map->width);
	collected = map->collectibles_count;
	start_pos.x = map->player.pos.x;
	start_pos.y = map->player.pos.y;
	if (!dfs_collectibles(map, visited, start_pos, &collected))
	{
		ft_printf("Error: Not all collectibles can be collected\n");
		free_visited(visited, map->height);
		exit(1);
	}
	reset_visited(visited, map->height, map->width);
	if (!dfs_exit(map, visited, start_pos))
	{
		ft_printf("Error: No valid path from player to exit\n");
		free_visited(visited, map->height);
		exit(1);
	}
	free_visited(visited, map->height);
	ft_printf("Valid path exists from player to exit\n");
	return (TRUE);
}
