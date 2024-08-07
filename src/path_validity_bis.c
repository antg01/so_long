/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validity_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:59:53 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 13:04:23 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to check if a given position is an exit.
 *
 * This function checks if the cell at the specified coordinates
 * (x, y) in the map grid
 * is an exit.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int x: The x-coordinate of the position to check.
 * - int y: The y-coordinate of the position to check.
 *
 * Return:
 * - bool: Returns true if the position is an exit, otherwise false.
 */
int	check_exit(t_map *map, int x, int y)
{
	return (map->grid[y][x] == EXIT);
}

/*
 * Function to initialize the visited array for DFS traversal.
 *
 * This function allocates memory for a 2D array of boolean values to keep track
 * of visited positions during DFS traversal.
 * Each element in the array is initialized
 * to false.
 *
 * Parameters:
 * - int height: The height of the game map (number of rows).
 * - int width: The width of the game map (number of columns).
 *
 * Return:
 * - bool**: Returns a pointer to the 2D array of boolean values.
 */
int	**initialize_visited(int height, int width)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(height * sizeof(int *));
	if (!visited)
		exit(1);
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(width * sizeof(int));
		if (!visited[i])
		{
			free(visited);
			exit(1);
		}
		j = 0;
		while (j < width)
		{
			visited[i][j] = FALSE;
			j++;
		}
		i++;
	}
	return (visited);
}

/*
 * Function to free the allocated memory for the visited array.
 *
 * This function frees the memory allocated for each row in the visited array
 * and then frees the memory allocated for the array itself.
 *
 * Parameters:
 * - bool **visited: Pointer to the 2D array of boolean values to be freed.
 * - int height: The height of the visited array (number of rows).
 */
void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
