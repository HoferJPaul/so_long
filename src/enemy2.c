/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:21:44 by phofer            #+#    #+#             */
/*   Updated: 2025/09/15 14:40:57 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	enemy_can_enter(char tile)
{
	if (tile == TILE_WALL || tile == TILE_EXIT || tile == TILE_COLLECT
		|| tile == TILE_ENEMY)
		return (0);
	return (1);
}

static void	rand_dir_xy(int dir, t_enemy *e, int *nx, int *ny)
{
	*nx = e->x;
	*ny = e->y;
	if (dir == 0)
		(*ny)--;
	else if (dir == 1)
		(*nx)++;
	else if (dir == 2)
		(*ny)++;
	else if (dir == 3)
		(*nx)--;
}

static int	check_player_collision(t_data *d, int nx, int ny)
{
	if (nx == d->player_x && ny == d->player_y)
	{
		if (!d->game_over)
			handle_enemy(d);
		return (1);
	}
	return (0);
}

static int	try_enemy_move(t_data *d, t_enemy *e, int dir)
{
	int		nx;
	int		ny;
	char	tile;

	rand_dir_xy(dir, e, &nx, &ny);
	if (check_player_collision(d, nx, ny))
		return (1);
	tile = d->map[ny][nx];
	if (enemy_can_enter(tile))
	{
		d->map[e->y][e->x] = TILE_FLOOR;
		e->x = nx;
		e->y = ny;
		d->map[e->y][e->x] = TILE_ENEMY;
		render(d);
		return (1);
	}
	return (0);
}

void	enemy_step(t_data *d, t_enemy *e)
{
	int	dir;
	int	try;

	if (d->game_over)
		return ;
	dir = rand() % 4;
	try = 0;
	while (try < 4)
	{
		if (try_enemy_move(d, e, (dir + try) % 4))
			return ;
		try++;
	}
}
