/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:46:30 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 18:45:47 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		++i;
	}
	free(data->map);
	data->map = NULL;
}

static void	destroy_img(void *mlx, t_img *slot)
{
	if (mlx && slot && slot->img)
	{
		mlx_destroy_image(mlx, slot->img);
		slot->img = NULL;
	}
}

void	free_textures(t_data *data)
{
	if (!data)
		return ;
	destroy_img(data->mlx, &data->wall);
	destroy_img(data->mlx, &data->floor);
	destroy_img(data->mlx, &data->player_front);
	destroy_img(data->mlx, &data->player_back);
	destroy_img(data->mlx, &data->player_side_r);
	destroy_img(data->mlx, &data->player_side_l);
	destroy_img(data->mlx, &data->enemy_front);
	destroy_img(data->mlx, &data->enemy_back);
	destroy_img(data->mlx, &data->enemy_side_r);
	destroy_img(data->mlx, &data->enemy_side_l);
	destroy_img(data->mlx, &data->collectible);
	destroy_img(data->mlx, &data->exit_closed);
	destroy_img(data->mlx, &data->exit_open);
	destroy_img(data->mlx, &data->win_img);
	destroy_img(data->mlx, &data->lose_img);
	destroy_img(data->mlx, &data->text_bg);
}

void	close_windows(t_data *data)
{
	if (!data || !data->mlx)
		return ;
	if (data->mlx_win)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		data->mlx_win = NULL;
	}
	if (data->win_screen)
	{
		mlx_destroy_window(data->mlx, data->win_screen);
		data->win_screen = NULL;
	}
	if (data->lose_screen)
	{
		mlx_destroy_window(data->mlx, data->lose_screen);
		data->lose_screen = NULL;
	}
}

void	cleanup_game(t_data *data)
{
	if (!data)
		exit(0);
	free_textures(data);
	enemies_free(data);
	close_windows(data);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free_map(data);
	data->map = NULL;
	exit(0);
}
