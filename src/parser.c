/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:22:12 by angerard          #+#    #+#             */
/*   Updated: 2024/08/06 17:26:46 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to read the dimensions of the map from a file.
 *
 * This function opens the map file, reads its dimensions
 * (number of lines and width), and allocates memory for the map grid.
 * If any step fails, it prints an error message and returns false.
 *
 * Parameters:
 * - const char *filename: The name of the map file to read.
 * - t_map *map: Pointer to the map structure to store the dimensions and grid.
 * - int *line_count: Pointer to store the number of lines in the map.
 * - int *width: Pointer to store the width of the map.
 *
 * Return:
 * - bool: Returns true if the dimensions are successfully read
 * and memory is allocated, otherwise returns false.
 */
int	read_map_dimensions(const char *filename, t_map *map, int *line_count,
		int *width)
{
	int	fd;

	if (!open_file(filename, &fd))
		return (FALSE);
	init_dimensions(line_count, width);
	ft_printf("Reading map file...\n");
	read_and_process_line(fd, line_count, width);
	ft_printf("Map dimensions: (%d x %d)\n", *line_count, *width);
	map->grid = malloc(sizeof(char *) * (*line_count));
	if (!map->grid)
	{
		ft_printf("Error allocating memory for grid");
		close(fd);
		return (FALSE);
	}
	map->width = *width;
	map->height = *line_count;
	close(fd);
	return (TRUE);
}

/*
 * Function to allocate memory for a row in the game map grid.
 *
 * This function allocates memory for a single row in the game map grid. If the
 * allocation fails, it prints an error message and returns false.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int i: The index of the row to allocate.
 * - int width: The width of the map (number of columns).
 *
 * Return:
 * - bool: Returns true if the memory allocation is successful, otherwise false.
 */
int	allocate_grid_row(t_map *map, int i, int width)
{
	map->grid[i] = malloc(width + 1);
	if (!map->grid[i])
	{
		ft_printf("Error allocating memory for grid row");
		return (FALSE);
	}
	return (TRUE);
}

/*
 * Function to process a line from the map file and update the game map grid.
 *
 * This function cleans a line from the map file, allocates memory for
 * the corresponding row in the map grid, copies the cleaned line into the grid,
 * and updates the player's position if found. If any step fails,returns false.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - char *line: The line to be processed.
 * - int i: The index of the row to process.
 * - int width: The width of the map (number of columns).
 *
 * Return:
 * - bool: Returns true if the line is successfully processed
 * and memory is allocated, otherwise returns false.
 */
int	process_line(t_map *map, char *line, int i, int width)
{
	int	j;

	line = clean_line(line);
	if (!allocate_grid_row(map, i, width))
		return (FALSE);
	ft_strncpy(map->grid[i], line, width);
	map->grid[i][width] = '\0';
	j = 0;
	while (j < width)
	{
		update_player_position(map, i, j);
		j++;
	}
	free(line);
	return (TRUE);
}

/*
 * Function to read and fill the game map data from a file.
 *
 * This function opens the map file, resets the file pointer, initializes
 * the player's position, processes each line of the map file to fill
 * the game grid, and verifies that a player position is found.
 * If any step fails, it returns false.
 *
 * Parameters:
 * - const char *filename: The name of the map file to read.
 * - t_map *map: Pointer to map struct to store the grid and player pos.
 * - int width: The width of the map (number of columns).
 *
 * Return:
 * - bool: Returns true if the map data is successfully read and processed,
 *         otherwise returns false.
 */
int	fill_map_data(const char *filename, t_map *map, int width)
{
	int		fd;
	char	*line;
	int		i;

	if (!open_file(filename, &fd))
		return (FALSE);
	lseek(fd, 0, SEEK_SET);
	init_player_position(map);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!process_line(map, line, i, width))
			return (FALSE);
		line = get_next_line(fd);
		i++;
	}
	if (map->player.pos.x == -1 || map->player.pos.y == -1)
	{
		ft_printf("Error: No player position found in map\n");
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

/*
 * Function to parse the game map from a file.
 *
 * This function reads the dimensions of the map, allocates memory for the grid,
 * fills the map data, and verifies the player's position.
 * If any step fails, returns false.
 *
 * Parameters:
 * - const char *filename: The name of the map file to read.
 * - t_map *map: Pointer to the map structure to store the grid and dimensions.
 *
 * Return:
 * - bool: Returns true if the map is successfully parsed,
 *         otherwise returns false.
 */
int	parser_map(const char *filename, t_map *map)
{
	int	line_count;
	int	width;

	if (!read_map_dimensions(filename, map, &line_count, &width))
		return (FALSE);
	if (!fill_map_data(filename, map, width))
		return (FALSE);
	count_collectibles(map);
	return (TRUE);
}
