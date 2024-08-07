/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:24:57 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 14:04:40 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
 * Main function of the program.
 *
 * This function initializes the necessary variables, checks the arguments
 * passed to the program, loads and parses the game map, initializes the game,
 * loads the necessary images, and starts the main game loop.
 * The function returns 0 if the program terminates successfully.
 */
int	main(int argc, char **argv)
{
	t_vars	vars;
	int		img_width;
	int		img_height;

	init_map(&vars, &vars.map);
	if (argc != 2)
		return (ft_printf("Error: <%s> map_file can't open\n", argv[0]), 1);
	if (!parser_map(argv[1], &vars.map))
		return (ft_printf("Failed to read map\n"), 1);
	if (!init_game(&vars, &vars.map))
		return (ft_printf("Failed to initialize mlx or create window\n"), 1);
	map_error_checker(&vars.map, vars.map.height, vars.map.width);
	load_images(&vars, &vars.map, &img_width, &img_height);
	render_map(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_loop_hook(vars.mlx, animate, &vars);
	mlx_loop(vars.mlx);
	free_map(&vars, &vars.map);
	return (0);
}
