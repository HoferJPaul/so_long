/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:34:30 by phofer            #+#    #+#             */
/*   Updated: 2025/09/11 15:34:34 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_text(t_data *data)
{
	char	moves_str[32];
	char	*temp;

	if (data->text_bg.img)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->text_bg.img, 5, 5);
	}
	temp = ft_itoa(data->moves);
	if (temp)
	{
		ft_strcpy(moves_str, "Moves: ");
		ft_strcat(moves_str, temp);
		mlx_string_put(data->mlx, data->mlx_win, 20, 20, 0xFFFFFF, moves_str);
		free(temp);
	}
	if (data->last_message[0] != '\0')
	{
		mlx_string_put(data->mlx, data->mlx_win, 100, 20, 0xFFFF00,
			data->last_message);
	}
}

void	set_message(t_data *data, const char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	if (len >= sizeof(data->last_message))
		len = sizeof(data->last_message) - 1;
	ft_strncpy(data->last_message, msg, len);
	data->last_message[len] = '\0';
}

void	set_message_with_number(t_data *data, const char *prefix, int number,
		const char *suffix)
{
	char	buffer[MAX_MSG_LEN];
	char	*num_str;

	num_str = ft_itoa(number);
	if (num_str)
	{
		ft_strcpy(buffer, prefix);
		ft_strcat(buffer, num_str);
		ft_strcat(buffer, suffix);
		free(num_str);
		set_message(data, buffer);
	}
	else
	{
		set_message(data, prefix);
	}
}

void	clear_message(t_data *data)
{
	data->last_message[0] = '\0';
}
