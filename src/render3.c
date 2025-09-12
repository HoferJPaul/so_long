/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:08:39 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 15:55:28 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_data *data, int x, int y, char c)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->floor.img, x, y);
	if (c == '1')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->wall.img,
			x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->collectible.img, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->current_exit->img, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->current_player->img, x, y);
	else if (c == 'X')
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->current_enemy->img, x, y);
}
