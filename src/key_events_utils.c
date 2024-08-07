/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:38:56 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 10:09:15 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to count the number of collectibles in the game map.
 *
 * This function iterates through the game map grid and counts the number of
 * collectible items. It updates the collectibles_count with the total number
 * of collectibles found.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 */
void	count_collectibles(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == COLLECTIBLE)
				map->collectibles_count++;
			x++;
		}
		y++;
	}
}

/*
 * Function to handle collectible items on the game map.
 *
 * This function checks if the current cell contains a collectible. If it does,
 * it decrements the collectibles_count and marks the cell as empty.
 *
 * Parameters:
 * - t_map *map: Pointer to the map structure containing the game grid.
 * - int x: The x-coordinate of the current cell.
 * - int y: The y-coordinate of the current cell.
 */
void	handle_collectible(t_map *map, int x, int y)
{
	if (map->grid[y][x] == COLLECTIBLE)
	{
		map->collectibles_count--;
	}
}

/*
 * Function to update the player's position on the game map.
 *
 * This function updates the grid to reflect the player's new position
 * by marking the previous position as empty & setting the new position
 * to represent the player. It also updates the player's coordinates
 * in the map structure.
 *
 * Parameters:
 * - t_map *map: Pointer to the map struct containing the grid & player data.
 * - int x: The new x-coordinate for the player.
 * - int y: The new y-coordinate for the player.
 */
void	move_player_update(t_map *map, int x, int y)
{
	map->grid[map->player.pos.y][map->player.pos.x] = EMPTY;
	map->grid[y][x] = PLAYER;
	map->player.pos.x = x;
	map->player.pos.y = y;
}
