/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:29:00 by angerard          #+#    #+#             */
/*   Updated: 2024/07/05 12:41:59 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Function to render the number of moves on the game window.
 *
 * This function formats the number of moves into a string and displays it
 * on the game window at a specified position using the draw_text function.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 */
void	render_moves(t_vars *vars)
{
	char	moves_str[12];

	sprintf(moves_str, "Moves: %d", vars->moves);
	draw_text(vars, 5, 49, moves_str);
}
