/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:11:25 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 17:49:58 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_exit(t_data *data, int keycode)
{
	if (data->items_left > 0)
	{
		set_message(data, "Coffee isn't ready yet!");
		ft_printf("Exit locked! Collect all items first.\n");
		push_back(data, keycode);
		return (0);
	}
	else
	{
		data->moves++;
		ft_printf("You win! Moves: %d\n", data->moves);
		data->game_over = 1;
		show_win_screen(data);
		mlx_loop_end(data->mlx);
		return (0);
	}
}

void	update_player_position(t_data *data, int new_x, int new_y)
{
	data->map[data->player_y][data->player_x] = '0';
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[data->player_y][data->player_x] = 'P';
}

int	handle_enemy(t_data *data)
{
	data->game_over = 1;
	ft_printf("You were stung by angry wasps");
	show_lose_screen(data);
	mlx_loop_end(data->mlx);
	return (0);
}
