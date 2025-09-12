/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:04:36 by phofer            #+#    #+#             */
/*   Updated: 2025/09/11 18:25:20 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(t_data *data)
{
	size_t	width;
	int		i;

	if (!data->map || !data->map[0])
		return (0);
	width = ft_strlen(data->map[0]);
	i = 1;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) != width)
			return (0);
		i++;
	}
	return (1);
}

static int	check_borders(char **map, int height, int width)
{
	int	j;
	int	i;

	j = 0;
	while (j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
		j++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_surrounded(t_data *data)
{
	int	height;
	int	width;

	height = 0;
	if (!data->map || !data->map[0])
	{
		ft_printf("Error\nInvalid map\n");
		cleanup_game(data);
		exit(1);
	}
	width = ft_strlen(data->map[0]);
	while (data->map[height])
		height++;
	return (check_borders(data->map, height, width));
}
