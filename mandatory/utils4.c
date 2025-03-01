/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:44:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 14:40:28 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_window_fail(t_info *data)
{
	free_minilbx(data);
	ft_error("mlx_window failed!!");
	exit(EXIT_FAILURE);
}

void	free_images2(t_info *data)
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
	free_images3(data);
}

int	cross_close(t_info *data)
{
	free_images(data);
	free_minilbx(data);
	exit(EXIT_FAILURE);
}

void	load_enemy(t_info *data)
{
	data->enemy[0] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/enemy/0.xpm", &data->width, &data->height);
	data->enemy[1] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/enemy/1.xpm", &data->width, &data->height);
	data->enemy[2] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/enemy/2.xpm", &data->width, &data->height);
	data->enemy[3] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/enemy/3.xpm", &data->width, &data->height);
	data->enemy[4] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/enemy/4.xpm", &data->width, &data->height);
}

void	window_size_error(t_info *data)
{
	if (data->row * data->width > 1920 || data->column * data->height > 1060)
	{
		free_map(&data);
		free_error(data, "Oops! map's SIZE is huge 😓");
	}
}
