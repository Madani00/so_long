/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:37:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/20 12:21:11 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_map(s_info **data)
{
	int	i;

	i = 0;
	while (i < (*data)->column)
	{
		free((*data)->map[i]);
		free((*data)->c_map[i]);
		i++;
	}
	free((*data)->map);
	free((*data)->c_map);
}

void free_error(s_info *data, char *msg)
{
	free(data);
	write(2, "Error\n", 6);
	ft_error(msg);
}

void free_images(s_info *data)
{
	mlx_destroy_image(data->mlx, data->wall_img);
	mlx_destroy_image(data->mlx, data->wall_img1);
	mlx_destroy_image(data->mlx, data->empty_img);
	mlx_destroy_image(data->mlx, data->player_img);
	mlx_destroy_image(data->mlx, data->collect_img);
	mlx_destroy_image(data->mlx, data->door_img);
	mlx_destroy_image(data->mlx, data->player_down[0]);
	mlx_destroy_image(data->mlx, data->player_down[1]);
	mlx_destroy_image(data->mlx, data->player_down[2]);
	mlx_destroy_image(data->mlx, data->player_down[3]);
	mlx_destroy_image(data->mlx, data->player_right[0]);
	mlx_destroy_image(data->mlx, data->player_right[1]);
	mlx_destroy_image(data->mlx, data->player_right[2]);
	mlx_destroy_image(data->mlx, data->player_right[3]);
	mlx_destroy_image(data->mlx, data->player_left[0]);
	mlx_destroy_image(data->mlx, data->player_left[1]);
	mlx_destroy_image(data->mlx, data->player_left[2]);
	mlx_destroy_image(data->mlx, data->player_left[3]);
	mlx_destroy_image(data->mlx, data->player_up[0]);
	mlx_destroy_image(data->mlx, data->player_up[1]);
	mlx_destroy_image(data->mlx, data->player_up[2]);
	mlx_destroy_image(data->mlx, data->player_up[3]);
}

void free_minilbx(s_info *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(&data);
	free(data);
}
