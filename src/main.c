/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:52:40 by phofer            #+#    #+#             */
/*   Updated: 2025/09/12 16:51:48 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	read_map(t_data *data, char *argv)
{
	int		fd;
	char	*line;
	int		i;
	int		height;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error, failed to open file (count_lines)\n", 1));
	height = count_lines(fd);
	if (height < 0)
		return (1);
	data->map = malloc(sizeof(char *) * (height + 1));
	if (!data->map)
		return (ft_printf("Error, failed to open map (read_map)\n", 1));
	fd = open(argv, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while ((line))
	{
		remove_newline(line);
		data->map[i++] = line;
		line = get_next_line(fd);
	}
	data->map[i] = NULL;
	close(fd);
	return (0);
}

int	validate_map(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		ft_printf("Error, specify one map .ber");
		return (0);
	}
	len = ft_strlen(argv[1]);
	if ((len <= 9) || (ft_strcmp(argv[1] + len - 4, ".ber") != 0))
	{
		ft_printf("Error, files must be *.ber");
		return (0);
	}
	return (1);
}

static int	init_game(t_data *data)
{
	t_img	img;

	set_window_size(data, &img);

	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf("Error\nMLX init failed\n"), 0);
	data->mlx_win = mlx_new_window(data->mlx, img.width, img.height, "So Long");
	if (!data->mlx_win)
		return (ft_printf("Error\nWindow creation failed\n"), 0);
	if (load_img(data) == 1)
		return (ft_printf("Error\nLoad Textures failed\n"), 0);
	if (find_player(data))
		return (ft_printf("Error\nPlayer 'P' not found in map\n"), 0);
	enemies_init(data);
	mlx_loop_hook(data->mlx, enemies_tick, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);

	return (1);
}


int	ft_game(t_data *data, int argc, char **argv)
{
	if (!validate_map(argc, argv))
		return (1);
	if (read_map(data, argv[1]) == 1)
		return (cleanup_game(data),
			ft_printf("Error\nFailed to read map\n"), 1);
	if (!data->map)
		return (cleanup_game(data),
			ft_printf("Error\nFailed to read map\n"), 1);
	if (!check_char(data))
		return (cleanup_game(data),
			ft_printf("Error\nFailed to Parse Map\n"), 1);
	if (!validate_path(data))
		return (cleanup_game(data), ft_printf("Error\nInvalid map path\n"), 1);
	if (!init_game(data))
		return (cleanup_game(data), 1);
	set_message(data, "Let's make some coffee!!!");
	render(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ft_game(&data, argc, argv) == 1)
		exit(1);
	mlx_key_hook(data.mlx_win, handle_keypress, &data);
	mlx_loop(data.mlx);
	cleanup_game(&data);
	return (0);
}
