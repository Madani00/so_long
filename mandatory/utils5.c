/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:21:44 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/26 22:15:03 by eamchart         ###   ########.fr       */
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
	if (data->e_nmb[data->e_index].e_x == data->player_x && data->e_nmb[data->e_index].e_y == data->player_y)
	{
		free_images(data);
		free_minilbx(data);
		exit(EXIT_FAILURE);
	}
}
