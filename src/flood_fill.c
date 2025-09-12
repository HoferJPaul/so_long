/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:34:56 by phofer            #+#    #+#             */
/*   Updated: 2025/09/11 17:35:12 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(t_data *data)
{
	int		height;
	int		i;

	height = 0;
	while (data->map[height])
		height++;
	data->map_cpy = malloc(sizeof(char *) * (height + 1));
	if (!data->map_cpy)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		data->map_cpy[i] = malloc(sizeof(char) * (ft_strlen(data->map[i]) + 1));
		if (!data->map_cpy[i])
		{
			while (--i >= 0)
				free(data->map_cpy[i]);
			free(data->map_cpy);
			return (NULL);
		}
		ft_strcpy(data->map_cpy[i], data->map[i]);
	}
	data->map_cpy[height] = NULL;
	return (data->map_cpy);
}

void	flood_fill_recursive(t_data *data, int x, int y)
{
	if (!data->map_cpy[y] || !data->map_cpy[y][x]
			|| data->map_cpy[y][x] == '1' || data->map_cpy[y][x] == 'F')
		return ;
	if (data->map_cpy[y][x] == 'E'
			&& data->collectibles_found < data->items_total)
		return ;
	if (data->map_cpy[y][x] == 'C')
		data->collectibles_found++;
	else if (data->map_cpy[y][x] == 'E')
		data->exit_found = 1;
	data->map_cpy[y][x] = 'F';
	flood_fill_recursive(data, x + 1, y);
	flood_fill_recursive(data, x - 1, y);
	flood_fill_recursive(data, x, y + 1);
	flood_fill_recursive(data, x, y - 1);
}

static int	check_collectibles(t_data *data)
{
	data->collectibles_found = 0;
	data->exit_found = 0;
	flood_fill_recursive(data, data->player_x, data->player_y);
	if (data->collectibles_found != data->items_total)
	{
		ft_printf("Error\nNot all collectibles are reachable\n");
		return (0);
	}
	return (1);
}

int	validate_helper(t_data	*data)
{
	copy_map(data);
	if (!data->map_cpy)
	{
		ft_printf("Error\nFailed to allocate memory for map validation\n");
		return (0);
	}
	if (!check_exit(data))
	{
		free_map_copy(data->map_cpy);
		return (0);
	}
	free_map_copy(data->map_cpy);
	return (1);
}

int	validate_path(t_data *data)
{
	if (find_player(data) != 0)
	{
		ft_printf("Error\nPlayer position not found\n");
		return (0);
	}
	copy_map(data);
	if (!data->map_cpy)
	{
		ft_printf("Error\nFailed to allocate memory for map validation\n");
		return (0);
	}
	if (!check_collectibles(data))
	{
		free_map_copy(data->map_cpy);
		return (0);
	}
	free_map_copy(data->map_cpy);
	validate_helper(data);
	return (1);
}
