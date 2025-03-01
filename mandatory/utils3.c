/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:05:49 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 14:36:30 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	press_keys(t_info *data, int key)
{
	if (key == A && data->map[data->player_x][data->player_y - 1] != '1')
	{
		data->direction = 3;
		data->player_y--;
	}
	else if (key == D && data->map[data->player_x][data->player_y + 1] != '1')
	{
		data->direction = 2;
		data->player_y++;
	}
	else if (key == W && data->map[data->player_x - 1][data->player_y] != '1')
	{
		data->direction = 1;
		data->player_x--;
	}
	else if (key == S && data->map[data->player_x + 1][data->player_y] != '1')
	{
		data->direction = 0;
		data->player_x++;
	}
	else
	{
		data->direction = -1;
	}
}

void	collect_coins(t_info *data)
{
	if (data->map[data->player_x][data->player_y] == 'C')
	{
		data->collect--;
		data->map[data->player_x][data->player_y] = '0';
	}
}

void	free_all_mlx(t_info *data)
{
	free_images(data);
	free_minilbx(data);
	ft_error("One of the Images failed!! ❌");
	exit(EXIT_FAILURE);
}

void	images_failed(t_info *data)
{
	load_enemy(data);
	if (!data->wall_img || !data->wall_img1 || !data->empty_img
		|| !data->player_img || !data->collect_img || !data->door_img)
		free_all_mlx(data);
	if (!data->player_down[0] || !data->player_down[1]
		|| !data->player_down[2] || !data->player_down[3])
		free_all_mlx(data);
	if (!data->player_right[0] || !data->player_right[1]
		|| !data->player_right[2] || !data->player_right[3])
		free_all_mlx(data);
	if (!data->player_left[0] || !data->player_left[1]
		|| !data->player_left[2] || !data->player_left[3])
		free_all_mlx(data);
	if (!data->player_up[0] || !data->player_up[1]
		|| !data->player_up[2] || !data->player_up[3])
		free_all_mlx(data);
	if (!data->enemy[0] || !data->enemy[1] || !data->enemy[2]
		|| !data->enemy[3] || !data->enemy[4])
		free_all_mlx(data);
}

void	load_images2(t_info *data)
{
	data->player_right[0] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/right/0.xpm", &data->width, &data->height);
	data->player_right[1] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/right/1.xpm", &data->width, &data->height);
	data->player_right[2] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/right/2.xpm", &data->width, &data->height);
	data->player_right[3] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/right/3.xpm", &data->width, &data->height);
	data->player_left[0] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/left/0.xpm", &data->width, &data->height);
	data->player_left[1] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/left/1.xpm", &data->width, &data->height);
	data->player_left[2] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/left/2.xpm", &data->width, &data->height);
	data->player_left[3] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/left/3.xpm", &data->width, &data->height);
	data->player_up[0] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/up/0.xpm", &data->width, &data->height);
	data->player_up[1] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/up/1.xpm", &data->width, &data->height);
	data->player_up[2] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/up/2.xpm", &data->width, &data->height);
	data->player_up[3] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/up/3.xpm", &data->width, &data->height);
	images_failed(data);
}
