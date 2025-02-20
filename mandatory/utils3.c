/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:05:49 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/20 14:06:04 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void press_keys(s_info *data)
{
	if ((keycode == A) && data->map[data->player_x][data->player_y - 1] != '1')
	{
		data->direction = 3;
		data->player_y--;
	}
	else if ((keycode == D) && data->map[data->player_x][data->player_y + 1] != '1')
	{
		data->direction = 2;
		data->player_y++;
	}
	else if ((keycode == W) && data->map[data->player_x - 1][data->player_y] != '1')
	{
		data->direction = 1;
		data->player_x--;
	}
	else if ((keycode == S) && data->map[data->player_x + 1][data->player_y] != '1')
	{
		data->direction = 0;
		data->player_x++;
	}
	else
	{
		data->direction = -1;
	}
}
