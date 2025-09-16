/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:14:43 by phofer            #+#    #+#             */
/*   Updated: 2025/09/15 14:40:45 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int	enemies_tick(t_data *d)
{
	int		i;
	long	t;

	if (!d->enemies.arr || d->enemies.count <= 0)
		return (0);
	t = now_ms();
	if (t - d->enemies.last_ms < d->enemies.interval_ms)
		return (0);
	d->enemies.last_ms = t;
	i = 0;
	while (i < d->enemies.count)
	{
		enemy_step(d, &d->enemies.arr[i]);
		i++;
	}
	return (0);
}

static int	process_enemy_tile(t_data *d, t_enemy *arr, int x, int y)
{
	static int	n = 0;

	if (d->map[y][x] == TILE_ENEMY)
	{
		arr[n].x = x;
		arr[n].y = y;
		arr[n].dir = rand() % 4;
		n++;
		return (1);
	}
	return (0);
}

static int	collect_enemies_from_map(t_data *d, t_enemy *arr, int cap)
{
	int	y;
	int	x;
	int	n;

	n = 0;
	y = 0;
	while (d->map[y] && n < cap)
	{
		x = 0;
		while (d->map[y][x] && n < cap)
		{
			if (process_enemy_tile(d, arr, x, y))
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static int	count_enemies_in_map(t_data *d)
{
	int	h;
	int	w;
	int	count;

	h = 0;
	count = 0;
	while (d->map[h])
	{
		w = 0;
		while (d->map[h][w])
		{
			if (d->map[h][w] == TILE_ENEMY)
				count++;
			w++;
		}
		h++;
	}
	return (count);
}

int	enemies_init(t_data *d)
{
	int	count;

	srand((unsigned int)time(NULL));
	count = count_enemies_in_map(d);
	if (count <= 0)
		return (0);
	d->enemies.arr = (t_enemy *)malloc(sizeof(t_enemy) * count);
	if (!d->enemies.arr)
		return (0);
	d->enemies.count = collect_enemies_from_map(d, d->enemies.arr, count);
	d->enemies.interval_ms = ENEMY_SPEED;
	d->enemies.last_ms = 0;
	return (1);
}
