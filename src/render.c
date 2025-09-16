/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:07:47 by phofer            #+#    #+#             */
/*   Updated: 2025/09/15 14:27:25 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	set_window_size(t_data *data, t_img *img)
{
	int	width;
	int	i;

	width = ft_strlen(data->map[0]);
	i = 0;
	while (data->map[i])
		++i;
	img->width = width * TILE_SIZE;
	img->height = i * TILE_SIZE;
	return (1);
}

void	text_window(t_data *data)
{
	int	*addr;
	int	size;
	int	i;

	data->text_bg.img = mlx_new_image(data->mlx, 300, 100);
	if (data->text_bg.img)
	{
		addr = (int *)mlx_get_data_addr(data->text_bg.img,
				&data->text_bg.width,
				&data->text_bg.height,
				&data->text_bg.bits_per_pixel);
		size = 300 * 100;
		i = 0;
		while (i < size)
		{
			addr[i] = 0x000000;
			i++;
		}
	}
}

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
