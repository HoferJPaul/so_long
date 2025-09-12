/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:22:15 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 15:35:08 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(int fd)
{
	int		height;
	char	*line;

	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (height);
}

void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	count_character(t_data *data, char target, int *count)
{
	int	i;
	int	j;

	i = 0;
	*count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == target)
				(*count)++;
			else if (target == '0' && data->map[i][j] != 'P'
				&& data->map[i][j] != 'E' && data->map[i][j] != 'C'
				&& data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'X')
			{
				ft_printf("Error\nInvalid char: %c\n", data->map[i][j]);
				cleanup_game(data);
				exit(1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_characters(t_data *data)
{
	int	player;
	int	exitx;
	int	collectible;
	int	floor;

	count_character(data, 'P', &player);
	count_character(data, 'E', &exitx);
	count_character(data, 'C', &collectible);
	count_character(data, '0', &floor);
	if (player != 1)
	{
		ft_printf("Error\nMap must contain exactly one player (P)\n");
		cleanup_game(data);
		exit (1);
	}
	if (exitx != 1 || collectible < 1)
	{
		ft_printf("Error\nMap must contain exactly one exit (E) ");
		ft_printf("and collectable (C)\n");
		cleanup_game(data);
		exit(1);
	}
	data->items_total = collectible;
	data->items_left = collectible;
	return (1);
}

int	check_char(t_data *data)
{
	if (!is_rectangular(data))
	{
		ft_printf("Error\nMap is not rectangular\n");
		cleanup_game(data);
		exit(1);
	}
	if (!is_surrounded(data))
	{
		ft_printf("Error\nMap is not surrounded by walls\n");
		cleanup_game(data);
		exit(1);
	}
	validate_characters(data);
	return (1);
}
