/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:01:51 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 18:14:19 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_win_screen(t_data *data)
{
	if (!data->win_img.img || !data->mlx)
		return ;
	mlx_destroy_window(data->mlx, data->mlx_win);
	data->mlx_win = NULL;
	data->win_screen = mlx_new_window(data->mlx, 624, 416, "You Win!");
	if (!data->win_screen)
	{
		ft_printf("Warning: Failed to create win screen window\n");
		return ;
	}
	mlx_put_image_to_window(data->mlx, data->win_screen, data->win_img.img,
		0, 0);
	mlx_key_hook(data->win_screen, exit_on_key, data);
	mlx_hook(data->win_screen, 17, 0, close_window, data);
	mlx_loop(data->mlx);
}

void	show_lose_screen(t_data *data)
{
	if (!data->lose_img.img || !data->mlx)
		return ;
	mlx_destroy_window(data->mlx, data->mlx_win);
	data->mlx_win = NULL;
	data->lose_screen = mlx_new_window(data->mlx, 624, 416, "You Lose");
	if (!data->lose_screen)
	{
		ft_printf("Warning: Failed to create lose screen window\n");
		return ;
	}
	mlx_put_image_to_window(data->mlx, data->lose_screen, data->lose_img.img,
		0, 0);
	mlx_key_hook(data->lose_screen, exit_on_key, data);
	mlx_hook(data->lose_screen, 17, 0, close_window, data);
	mlx_loop(data->mlx);
}

int	push_back(t_data *data, int keycode)
{
	if (keycode == 119 || keycode == 65362)
		data->current_player = &data->player_front;
	else if (keycode == 115 || keycode == 65364)
		data->current_player = &data->player_back;
	else if (keycode == 97 || keycode == 65361)
		data->current_player = &data->player_side_r;
	else if (keycode == 100 || keycode == 65363)
		data->current_player = &data->player_side_l;
	else
	{
		ft_printf("error, keypress\n");
		return (0);
	}
	render(data);
	return (0);
}
