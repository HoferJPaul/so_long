/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:10:21 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 17:52:34 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_player_direction(t_data *data, int keycode, int *new_x,
		int *new_y)
{
	if (keycode == 119 || keycode == 65362)
	{
		(*new_y)--;
		data->current_player = &data->player_back;
	}
	else if (keycode == 115 || keycode == 65364)
	{
		(*new_y)++;
		data->current_player = &data->player_front;
	}
	else if (keycode == 97 || keycode == 65361)
	{
		(*new_x)--;
		data->current_player = &data->player_side_l;
	}
	else if (keycode == 100 || keycode == 65363)
	{
		(*new_x)++;
		data->current_player = &data->player_side_r;
	}
}

int	validate_move(t_data *data, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || !data->map[new_y]
		|| !data->map[new_y][new_x])
		return (0);
	if (data->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

int	handle_collectible(t_data *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] == 'C')
	{
		data->items_left--;
		set_message_with_number(data, "Item collected! ", data->items_left,
			" left");
		ft_printf("Item Collected! %d left\n", data->items_left);
		if (data->items_left == 0)
		{
			data->current_exit = &data->exit_open;
			set_message(data, "Coffee is ready!");
			ft_printf("All collected! Exit open.\n");
		}
		return (1);
	}
	return (0);
}

static int	process_movement(t_data *data, int keycode)
{
	int	new_x;
	int	new_y;

	if (data->game_over)
		return (0);
	set_message(data, "Yum yum coffee!");
	new_x = data->player_x;
	new_y = data->player_y;
	set_player_direction(data, keycode, &new_x, &new_y);
	if (!validate_move(data, new_x, new_y))
		return (0);
	handle_collectible(data, new_x, new_y);
	if (data->map[new_y][new_x] == 'E')
		return (handle_exit(data, keycode));
	if (data->map[new_y][new_x] == 'X')
		return (handle_enemy(data));
	update_player_position(data, new_x, new_y);
	data->moves++;
	ft_printf("Moves: %d\n", data->moves);
	render(data);
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 119 || keycode == 65362 || keycode == 115
		|| keycode == 65364 || keycode == 97 || keycode == 65361
		|| keycode == 100 || keycode == 65363)
	{
		return (process_movement(data, keycode));
	}
	else if (keycode == 65307)
	{
		cleanup_game(data);
		exit(0);
	}
	return (0);
}
