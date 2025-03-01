/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:21:44 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 12:24:15 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_images3(t_info *data)
{
	if (data->enemy[0])
		mlx_destroy_image(data->mlx, data->enemy[0]);
	if (data->enemy[1])
		mlx_destroy_image(data->mlx, data->enemy[1]);
	if (data->enemy[2])
		mlx_destroy_image(data->mlx, data->enemy[2]);
	if (data->enemy[3])
		mlx_destroy_image(data->mlx, data->enemy[3]);
	if (data->enemy[4])
		mlx_destroy_image(data->mlx, data->enemy[4]);
}

void touch_enemy(t_info *data)
{
	if ((data->e_nmb[data->e_index].e_x == data->player_x && data->e_nmb[data->e_index].e_y == data->player_y))
	{
		free_images(data);
		free_minilbx(data);
		exit(EXIT_FAILURE);
	}
}

void	if_door_enemy(t_info *data, int *k, int *i)
{
	if (data->map[*k][*i] == 'A')
	{
		data->e_nmb[data->e_index].e_x = *k;
		data->e_nmb[data->e_index].e_y = *i;
		data->e_nmb[data->e_index].moves = 0;
		data->e_index++;
	}
	if (data->map[*k][*i] == 'E')
	{
		data->door_x = *k;
		data->door_y = *i;
		data->map[*k][*i] = '0';
	}
}

int	wall_enemy_coin(char c)
{
	if (c != '1' && c != 'C' && c != 'A' && c != 'E')
		return (1);
	return (0);
}

void	idle_animation(t_info *data)
{
	if (data->e_index == data->enemy_nmb)
		data->e_index = 0;
	data->e_ani += 1;
}
