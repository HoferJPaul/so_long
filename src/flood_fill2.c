/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:23:53 by phofer            #+#    #+#             */
/*   Updated: 2025/09/11 16:26:50 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_copy(char **map_copy)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

int	check_exit(t_data *data)
{
	data->collectibles_found = data->items_total;
	data->exit_found = 0;
	flood_fill_recursive(data, data->player_x, data->player_y);
	if (!data->exit_found)
	{
		ft_printf("Error\nExit is not reachable after collecting all items\n");
		return (0);
	}
	return (1);
}
