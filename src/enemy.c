#include "so_long.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

static int	enemy_can_enter(char tile)
{
	if (tile == TILE_WALL || tile == TILE_EXIT || tile == TILE_COLLECT
		|| tile == TILE_ENEMY)
		return (0);
	return (1);
}

static void	rand_dir_xy(int dir, int x, int y, int *nx, int *ny)
{
	*nx = x;
	*ny = y;
	if (dir == 0)
		(*ny)--;
	else if (dir == 1)
		(*nx)++;
	else if (dir == 2)
		(*ny)++;
	else if (dir == 3)
		(*nx)--;
}

static void	enemy_step(t_data *d, t_enemy *e)
{
	int		dir;
	int		try;
	int		nx;
	int		ny;
	char	tile;

	if (d->game_over)
		return ;
	dir = rand() % 4;
	try = 0;
	while (try < 4)
	{
		rand_dir_xy((dir + try) % 4, e->x, e->y, &nx, &ny);
		tile = d->map[ny][nx];
		if (nx == d->player_x && ny == d->player_y)
		{
			if (!d->game_over)
			{
				handle_enemy(d);
			}
			return ;
		}
		if (enemy_can_enter(tile))
		{
			d->map[e->y][e->x] = TILE_FLOOR;
			//draw_tile(d, TILE_FLOOR, e->x, e->y);
			e->x = nx;
			e->y = ny;
			d->map[e->y][e->x] = TILE_ENEMY;
			render(d);
			//draw_tile(d, TILE_ENEMY, e->x, e->y);
			return ;
		}
		try++;
	}
}

static long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

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
			if (d->map[y][x] == TILE_ENEMY)
			{
				arr[n].x = x;
				arr[n].y = y;
				arr[n].dir = rand() % 4;
				n++;
			}
			x++;
		}
		y++;
	}
	return (n);
}

int	enemies_init(t_data *d)
{
	int	h;
	int	w;
	int	count;

	srand((unsigned int)time(NULL));
	h = 0;
	count = 0;
	while (d->map[h++])
	{
		w = 0;
		while (d->map[h - 1][w])
			count += (d->map[h - 1][w++] == TILE_ENEMY);
	}
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

void	enemies_free(t_data *d)
{
	if (d->enemies.arr)
		free(d->enemies.arr);
	d->enemies.arr = NULL;
	d->enemies.count = 0;
}

