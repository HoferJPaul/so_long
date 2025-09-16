/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:08:39 by phofer            #+#    #+#             */
/*   Updated: 2025/09/15 14:31:13 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <sys/time.h>
#include <time.h>

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

void	enemies_free(t_data *d)
{
	if (d->enemies.arr)
		free(d->enemies.arr);
	d->enemies.arr = NULL;
	d->enemies.count = 0;
}
