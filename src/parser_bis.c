/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:02:23 by angerard          #+#    #+#             */
/*   Updated: 2024/07/05 11:58:02 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to update the player's position on the game map.
 *
 * This function checks if the current cell in the map grid contains
 * the player character.
 * If so, it updates the player's position in the map structure.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int i: The row index of the current cell in the grid.
 * - int j: The column index of the current cell in the grid.
 */
void	update_player_position(t_map *map, int i, int j)
{
	if (map->grid[i][j] == PLAYER)
	{
		map->player.pos.x = j;
		map->player.pos.y = i;
	}
}

/*
 * Function to initialize the player's position.
 *
 * This function sets the player's position to an initial invalid state (-1, -1),
 * indicating that the player's position has not yet been set on the map.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the player's position.
 */
void	init_player_position(t_map *map)
{
	map->player.pos.x = -1;
	map->player.pos.y = -1;
}

/*
 * Function to open a file for reading.
 *
 * This function attempts to open the specified file in read-only mode. If the
 * file fails to open, it prints an error message and returns false. Otherwise,
 * it sets the file descriptor and returns true.
 *
 * Parameters:
 * - const char *filename: The name of the file to open.
 * - int *fd: Pointer to an integer where the file descriptor will be stored.
 *
 * Return:
 * - bool: Returns true if the file is successfully opened,
 *         otherwise returns false.
 */
int	open_file(const char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		ft_printf("Error opening file");
		return (FALSE);
	}
	return (TRUE);
}

/*
 * Function to initialize map dimensions.
 *
 * This function sets the initial values of line_count and width to zero.
 *
 * Parameters:
 * - int *line_count: Pointer to integer where number of lines will be stored.
 * - int *width: Pointer to integer where width of the map will be stored.
 */
void	init_dimensions(int *line_count, int *width)
{
	*line_count = 0;
	*width = 0;
}

/*
 * Function to read and process each line of the map file.
 *
 * This function reads each line of the map file, cleans the line, and updates
 * the map dimensions (line count and width). It uses get_next_line to read lines
 * from the file and clean_line to process each line.
 *
 * Parameters:
 * - int fd: The file descriptor of the open map file.
 * - int *line_count: Pointer to integer where number of lines will be stored.
 * - int *width: Pointer to integer where width of the map will be stored.
 */
void	read_and_process_line(int fd, int *line_count, int *width)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line = clean_line(line);
		if (*line_count == 0)
			*width = ft_strlen_sl(line);
		free(line);
		(*line_count)++;
		line = get_next_line(fd);
	}
}
