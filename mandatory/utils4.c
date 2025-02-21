/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:44:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/21 18:05:48 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_window_fail(s_info *data)
{
	free_minilbx(data);
	ft_error("mlx_window failed!!");
	exit(EXIT_FAILURE);
}

void	free_images2(s_info *data)
{
	if (data->player_right[2])
		mlx_destroy_image(data->mlx, data->player_right[2]);
	if (data->player_right[3])
		mlx_destroy_image(data->mlx, data->player_right[3]);
	if (data->player_left[0])
		mlx_destroy_image(data->mlx, data->player_left[0]);
	if (data->player_left[1])
		mlx_destroy_image(data->mlx, data->player_left[1]);
	if (data->player_left[2])
		mlx_destroy_image(data->mlx, data->player_left[2]);
	if (data->player_left[3])
		mlx_destroy_image(data->mlx, data->player_left[3]);
	if (data->player_up[0])
		mlx_destroy_image(data->mlx, data->player_up[0]);
	if (data->player_up[1])
		mlx_destroy_image(data->mlx, data->player_up[1]);
	if (data->player_up[2])
		mlx_destroy_image(data->mlx, data->player_up[2]);
	if (data->player_up[3])
		mlx_destroy_image(data->mlx, data->player_up[3]);
}
