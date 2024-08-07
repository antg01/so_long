/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:04:56 by angerard          #+#    #+#             */
/*   Updated: 2024/08/06 16:34:02 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/move_display.h"
#include "../includes/so_long.h"

/*
 * Function to handle the animation of the player's sprite.
 *
 * This function updates the player's sprite image based on the current frame,
 * and displays it in the game window. If the game is over or won,
 * it stops the animation.
 *
 * Parameters:
 * - void *param: Pointer to the vars structure containing game variables.
 *
 * Return:
 * - int: Always returns 0.
 */
void	load_and_display_player_image(t_vars *vars, int frame)
{
	int		img_width;
	int		img_height;
	char	frame_filename[50];

	if (vars->map.player.sprite.img)
	{
		mlx_destroy_image(vars->mlx, vars->map.player.sprite.img);
		vars->map.player.sprite.img = NULL;
	}
	sprintf(frame_filename, "%sfly%d.xpm", FRAME_PATH, frame);
	vars->map.player.sprite.img = mlx_xpm_file_to_image(vars->mlx,
			frame_filename, &img_width, &img_height);
	if (vars->map.player.sprite.img)
	{
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->map.player.sprite.img,
			vars->map.player.pos.x * TILE_SIZE,
			vars->map.player.pos.y * TILE_SIZE);
	}
	else
	{
		ft_printf("Error: Failed to load image: %s\n", frame_filename);
	}
}

int	animate(void *param)
{
	static int	frame = 1;
	t_vars		*vars;

	vars = (t_vars *)param;
	if (vars->game_over || vars->game_won)
		return (0);
	load_and_display_player_image(vars, frame);
	frame = (frame % NUM_FRAMES) + 1;
	usleep(FRAME_DELAY);
	return (0);
}

/*
 * Function to draw a character on the game window.
 *
 * This function draws a character representing a digit on the game window at a
 * specified position (x, y). It uses the mlx_pixel_put function
 * to set the pixel color.
 * Only characters between '0' and '9' are drawn.
 *
 * Parameters:
 * - t_vars *vars: Pointer to the vars structure containing game variables.
 * - int x: The x-coordinate where the character should be drawn.
 * - int y: The y-coordinate where the character should be drawn.
 * - char c: The character to be drawn. Only digits ('0' to '9') are valid.
 */
void	draw_char(t_vars *vars, int x, int y, char c)
{
	int	color;
	int	i;
	int	j;

	color = 0xFFFFFF;
	if (c < '0' || c > '9')
		return ;
	i = 0;
	while (i < CHAR_HEIGHT)
	{
		j = 0;
		while (j < CHAR_WIDTH)
		{
			if (digits[c - '0'][i][j] == '#')
				mlx_pixel_put(vars->mlx, vars->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/*
 * Function to render the end game screen.
 *
 * This function loads and displays the appropriate end game image
 * ("game over" or "you win") in the center of the game window.
 * If the image fails to load, it prints an error message.
 *
 * Parameters:
 * - t_vars *vars: Pointer to vars struct containing game variables.
 */
void	render_end_game(t_vars *vars)
{
	int		img_width;
	int		img_height;
	void	*end_game_img;
	int		x_pos;
	int		y_pos;

	if (vars->game_over)
		end_game_img = mlx_xpm_file_to_image(vars->mlx,
				"assets/end_game/game_over.xpm", &img_width,
				&img_height);
	else
		end_game_img = mlx_xpm_file_to_image(vars->mlx,
				"assets/end_game/you_win.xpm", &img_width,
				&img_height);
	if (!end_game_img)
	{
		ft_printf("Error: Failed to load game over image\n");
		return ;
	}
	x_pos = (vars->map.width * TILE_SIZE - img_width) / 2;
	y_pos = (vars->map.height * TILE_SIZE - img_height) / 2;
	mlx_put_image_to_window(vars->mlx, vars->win, end_game_img, x_pos, y_pos);
	mlx_destroy_image(vars->mlx, end_game_img);
	ft_printf("End Game. Exiting...\n");
}

/*
 * Function to draw a string of text on the game window.
 *
 * This function iterates through a string of text and uses
 * the draw_char function to draw each character at the specified
 * position (x, y). Each character is spaced
 * apart by the width of the character plus one pixel.
 *
 * Parameters:
 * - t_vars *vars: Pointer to vars struc containing game variables.
 * - int x: The x-coordinate where the text should start being drawn.
 * - int y: The y-coordinate where the text should start being drawn.
 * - char *text: The string of text to be drawn.
 */
void	draw_text(t_vars *vars, int x, int y, char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		draw_char(vars, x + i * (CHAR_WIDTH + 1), y, text[i]);
		i++;
	}
}
