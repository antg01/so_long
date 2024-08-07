/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:27:16 by angerard          #+#    #+#             */
/*   Updated: 2024/08/07 13:02:27 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* Constants */
# define WIN_NAME "SO_LONG"
# define TILE_SIZE 100
# define NUM_FRAMES 2
# define FRAME_PATH "assets/hero/"
# define FRAME_DELAY 60000
# define TRUE 1
# define FALSE 0

/* Includes */
# include "../mlx/mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Map characters */
# define WALL '1'
# define PLAYER 'P'
# define ENEMY 'X'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define EMPTY '0'

/* Structures */
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_sprite
{
	int			px_w;
	int			px_h;
	void		*img;
}				t_sprite;

typedef struct s_player
{
	t_point		pos;
	t_sprite	sprite;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles_count;
	t_sprite	*wall_img;
	t_sprite	*player_img;
	t_sprite	*enemy_img;
	t_sprite	*collectible_img;
	t_sprite	*exit_img;
	t_sprite	*empty_img;
	t_player	player;
}				t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			moves;
	int			game_over;
	int			game_won;
	t_map		map;
}				t_vars;

/* Function prototypes */
// init.c
int				init_game(t_vars *vars, t_map *map);
void			init_map(t_vars *vars, t_map *map);
void			load_images(t_vars *vars, t_map *map, int *img_width,
					int *img_height);
void			free_map(t_vars *vars, t_map *map);
void			error_exit(char *message);

// parser.c + bis
int				parser_map(const char *filename, t_map *map);
int				open_file(const char *filename, int *fd);
void			init_dimensions(int *line_count, int *width);
void			read_and_process_line(int fd, int *line_count, int *width);
int				read_map_dimensions(const char *filename, t_map *map,
					int *line_count, int *width);
int				allocate_grid_row(t_map *map, int i, int width);
void			update_player_position(t_map *map, int i, int j);
void			init_player_position(t_map *map);
int				process_line(t_map *map, char *line, int i, int width);
int				fill_map_data(const char *filename, t_map *map, int width);

// render.c
void			render_map(t_vars *vars);
void			render_tile(t_vars *vars, int x, int y);
void			*get_tile_image(t_vars *vars, char tile);

// key events + utils
int				key_hook(int keycode, t_vars *vars);
int				is_valid_move(t_map *map, int x, int y);
void			move_player(t_vars *vars, int x, int y);
void			move_player_update(t_map *map, int x, int y);
int				close_window(t_vars *vars);
void			count_collectibles(t_map *map);
void			handle_collectible(t_map *map, int x, int y);

// animate.c
int				animate(void *param);
void			draw_char(t_vars *vars, int x, int y, char c);
void			render_moves(t_vars *vars);
void			draw_text(t_vars *vars, int x, int y, char *text);
void			render_end_game(t_vars *vars);

// utils.c + bis
size_t			ft_strlen_sl(const char *s);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*clean_line(char *line);
void			check_file_exists(const char *filename);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int n);
void			key_count(int keycode, t_vars *vars);
void			*ft_memset(void *b, int c, size_t len);

// path_validity.c + bis
int				check_valid_path(t_map *map);
int				is_valid_position(t_map *map, int x, int y);
int				**initialize_visited(int height, int width);
void			reset_visited(int **visited, int height, int width);
int				dfs_collectibles(t_map *map, int **visited, t_point pos,
					int *collected);
int				dfs_exit(t_map *map, int **visited, t_point pos);
void			init_movements(int movements[4][2]);
void			update_position(t_point *pos, t_point *new_pos, int *movements,
					int i);
int				check_exit(t_map *map, int x, int y);
void			free_visited(int **visited, int height);

// check_error
void			map_error_checker(t_map *map, int rows, int cols);

#endif
