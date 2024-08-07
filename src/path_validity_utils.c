/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validity_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:37:37 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 13:04:43 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to check if a position is valid in the game map.
 *
 * This function determines if a given position (x, y) is within the boundaries
 * of the game map and not a wall. It returns true if the position is valid,
 * otherwise, it returns false.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int x: The x-coordinate of the position to check.
 * - int y: The y-coordinate of the position to check.
 *
 * Return:
 * - bool: Returns true if the position is within the map boundaries
 * and not a wall, otherwise returns false.
 */
int	is_valid_position(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height
		&& map->grid[y][x] != WALL && map->grid[y][x] != ENEMY)
		return (TRUE);
	return (FALSE);
}

/*
 * Function to reset the visited array for DFS traversal.
 *
 * This function sets all elements in the visited array to false (0) to reset
 * the state for a new DFS traversal.
 *
 * Parameters:
 * - bool **visited: Pointer to the 2D array of boolean values to be reset.
 * - int height: The height of the visited array (number of rows).
 * - int width: The width of the visited array (number of columns).
 */
void	reset_visited(int **visited, int height, int width)
{
	int	i;

	i = 0;
	while (i < height)
	{
		ft_memset(visited[i], 0, width * sizeof(int));
		i++;
	}
}

/*
 * Function to initialize movement directions for DFS traversal.
 *
 * This function sets the movement directions for DFS traversal in a 2D array.
 * The movements array contains four directions: up, down, left, and right.
 *
 * Parameters:
 * - int movements[4][2]: 2D array to store the movement directions.
 *
 * Detailed steps:
 * 1. Set movements[0] to [-1, 0] for moving up.
 * 2. Set movements[1] to [1, 0] for moving down.
 * 3. Set movements[2] to [0, -1] for moving left.
 * 4. Set movements[3] to [0, 1] for moving right.
 */
void	init_movements(int movements[4][2])
{
	movements[0][0] = -1;
	movements[0][1] = 0;
	movements[1][0] = 1;
	movements[1][1] = 0;
	movements[2][0] = 0;
	movements[2][1] = -1;
	movements[3][0] = 0;
	movements[3][1] = 1;
}

/*
 * Function to update the position based on movement directions.
 *
 * This function updates the new position (new_pos) based
 * on the current position (pos) and the specified movement direction.
 *
 * Parameters:
 * - t_point *pos: Pointer to the current position.
 * - t_point *new_pos: Pointer to the new position to be updated.
 * - int *movements: Array of movement directions.
 * - int i: Index of the movement direction to apply.
 */
void	update_position(t_point *pos, t_point *new_pos, int *movements, int i)
{
	new_pos->x = pos->x + movements[i * 2];
	new_pos->y = pos->y + movements[i * 2 + 1];
}
