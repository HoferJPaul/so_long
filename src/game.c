/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:19:04 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 17:55:24 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_on_key(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		cleanup_game(data);
		exit(0);
	}
	return (0);
}

int	close_window(t_data *data)
{
	cleanup_game(data);
	exit(0);
	return (0);
}

int	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->player_y = i;
				data->player_x = j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
