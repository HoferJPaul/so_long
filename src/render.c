/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:07:47 by phofer            #+#    #+#             */
/*   Updated: 2025/09/10 15:07:48 by phofer           ###   ########.fr       */
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
