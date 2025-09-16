/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:29:06 by phofer            #+#    #+#             */
/*   Updated: 2025/09/15 14:35:02 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 50
# define MAX_MSG_LEN 64
# define ENEMY_SPEED 500

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>

/* --- Enemy support ------------------------------------------------------- */

# define TILE_WALL       '1'
# define TILE_FLOOR      '0'
# define TILE_PLAYER     'P'
# define TILE_EXIT       'E'
# define TILE_COLLECT    'C'
# define TILE_ENEMY      'X'

typedef struct s_data	t_data;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	dir;
}	t_enemy;

typedef struct s_enemies
{
	t_enemy	*arr;
	int		count;
	long	last_ms;
	int		interval_ms;
}	t_enemies;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	int		bits_per_pixel;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*win_screen;
	void		*lose_screen;
	char		**map;
	char		**map_cpy;
	char		*map_file;
	char		last_message[MAX_MSG_LEN];
	char		message[MAX_MSG_LEN];
	t_img		text_bg;
	t_img		win_img;
	t_img		lose_img;
	t_img		wall;
	t_img		floor;
	t_img		collectible;
	t_img		exit_open;
	t_img		exit_closed;
	t_img		player_front;
	t_img		player_back;
	t_img		player_side_r;
	t_img		player_side_l;
	t_img		enemy_front;
	t_img		enemy_back;
	t_img		enemy_side_r;
	t_img		enemy_side_l;
	t_img		*current_enemy;
	t_img		*current_player;
	t_img		*current_exit;
	int			size_x;
	int			size_y;
	int			p_x;
	int			p_y;
	int			player_x;
	int			player_y;
	int			moves;
	int			items_total;
	int			items_left;
	int			game_over;
	int			collectibles_found;
	int			exit_found;
	t_player	player;
	t_enemies	enemies;
}	t_data;

/* main.c */
int		count_lines(int fd);
int		validate_map(int argc, char **argv);

/* game.c */
int		exit_on_key(int keycode, t_data *data);
int		close_window(t_data *data);
int		find_player(t_data *data);

/* game2.c */
void	show_win_screen(t_data *data);
void	show_lose_screen(t_data *data);
int		push_back(t_data *data, int keycode);

/* input.c */
int		handle_keypress(int keycode, t_data *data);
int		validate_move(t_data *data, int new_x, int new_y);
int		handle_collectible(t_data *data, int new_x, int new_y);

/* input2.c */
int		handle_exit(t_data *data, int keycode);
void	update_player_position(t_data *data, int new_x, int new_y);
int		handle_enemy(t_data *data);

/* render.c */
int		set_window_size(t_data *data, t_img *img);
void	text_window(t_data *data);
void	draw_tile(t_data *data, int x, int y, char c);

/* render2.c */
int		load_img(t_data *data);
void	render(t_data *data);

/* draw_text.c */
void	draw_text(t_data *data);
void	set_message(t_data *data, const char *msg);
void	set_message_with_number(t_data *data, const char *prefix,
			int number, const char *suffix);
void	clear_message(t_data *data);

/* map_parser.c */
int		is_rectangular(t_data *data);
int		is_surrounded(t_data *data);

/* map_parser2.c */
int		validate_characters(t_data *data);
int		check_char(t_data *data);
int		count_lines(int fd);
void	remove_newline(char *line);

/* flood_fill.c */
int		validate_path(t_data *data);
void	flood_fill_recursive(t_data *data, int x, int y);

/*food_fill2.c*/
void	free_map_copy(char **map_copy);
int		check_exit(t_data *data);

/* cleanup.c*/
void	free_map(t_data *data);
void	free_textures(t_data *data);
void	close_windows(t_data *data);
void	cleanup_game(t_data *data);

/* enemy API */
int		enemies_init(struct s_data *d);
void	enemies_free(struct s_data *d);
int		enemies_tick(struct s_data *d);
void	enemy_step(t_data *d, t_enemy *e);

/*helpers*/
void	enemies_free(t_data *d);
long	now_ms(void);

#endif
