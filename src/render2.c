/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:08:16 by phofer            #+#    #+#             */
/*   Updated: 2025/09/15 14:11:29 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_player_images(t_data *data)
{
	data->player_front.img = mlx_xpm_file_to_image(data->mlx,
			"textures/player_front.xpm", &data->player_front.width,
			&data->player_front.height);
	data->player_back.img = mlx_xpm_file_to_image(data->mlx,
			"textures/player_back.xpm", &data->player_back.width,
			&data->player_back.height);
	data->player_side_r.img = mlx_xpm_file_to_image(data->mlx,
			"textures/player_side_r.xpm", &data->player_side_r.width,
			&data->player_side_r.height);
	data->player_side_l.img = mlx_xpm_file_to_image(data->mlx,
			"textures/player_side_l.xpm", &data->player_side_l.width,
			&data->player_side_l.height);
	if (!data->player_front.img || !data->player_back.img
		|| !data->player_side_r.img || !data->player_side_l.img)
		return (1);
	return (0);
}

static int	load_enemy_images(t_data *data)
{
	data->enemy_front.img = mlx_xpm_file_to_image(data->mlx,
			"textures/enemy_front.xpm", &data->enemy_front.width,
			&data->enemy_front.height);
	data->enemy_back.img = mlx_xpm_file_to_image(data->mlx,
			"textures/enemy_back.xpm", &data->enemy_back.width,
			&data->enemy_back.height);
	data->enemy_side_r.img = mlx_xpm_file_to_image(data->mlx,
			"textures/enemy_side_r.xpm", &data->enemy_side_r.width,
			&data->enemy_side_r.height);
	data->enemy_side_l.img = mlx_xpm_file_to_image(data->mlx,
			"textures/enemy_side_l.xpm", &data->enemy_side_l.width,
			&data->enemy_side_l.height);
	if (!data->enemy_front.img || !data->enemy_back.img
		|| !data->enemy_side_r.img || !data->enemy_side_l.img)
		return (1);
	return (0);
}

static int	load_basic_images(t_data *data)
{
	data->wall.img = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm",
			&data->wall.width, &data->wall.height);
	data->floor.img = mlx_xpm_file_to_image(data->mlx, "textures/bg.xpm",
			&data->floor.width, &data->floor.height);
	data->collectible.img = mlx_xpm_file_to_image(data->mlx,
			"textures/item.xpm", &data->collectible.width,
			&data->collectible.height);
	data->exit_closed.img = mlx_xpm_file_to_image(data->mlx,
			"textures/exit_closed.xpm", &data->exit_closed.width,
			&data->exit_closed.height);
	data->exit_open.img = mlx_xpm_file_to_image(data->mlx,
			"textures/exit_open.xpm", &data->exit_open.width,
			&data->exit_open.height);
	data->win_img.img = mlx_xpm_file_to_image(data->mlx, "textures/win.xpm",
			&data->win_img.width, &data->win_img.height);
	data->lose_img.img = mlx_xpm_file_to_image(data->mlx, "textures/lose.xpm",
			&data->lose_img.width, &data->lose_img.height);
	if (!data->wall.img || !data->floor.img || !data->collectible.img
		|| !data->exit_closed.img || !data->exit_open.img
		|| !data->win_img.img || !data->lose_img.img)
		return (1);
	return (0);
}

int	load_img(t_data *data)
{
	if (load_basic_images(data) || load_player_images(data)
		|| load_enemy_images(data))
	{
		ft_printf("Error\nFailed to load one or more textures\n");
		return (1);
	}
	data->text_bg.img = mlx_new_image(data->mlx, 250, 25);
	data->current_player = &data->player_front;
	data->current_enemy = &data->enemy_front;
	data->current_exit = &data->exit_closed;
	return (0);
}

void	render(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			draw_tile(data, j * TILE_SIZE, i * TILE_SIZE, data->map[i][j]);
			++j;
		}
		++i;
	}
	draw_text(data);
}
