/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:37:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 11:13:34 by eamchart         ###   ########.fr       */
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

void	free_map(t_info **data)
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

void	free_error(t_info *data, char *msg)
{
	free(data);
	ft_error(msg);
}

void	free_images(t_info *data)
{
	if (data->wall_img)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (data->wall_img1)
		mlx_destroy_image(data->mlx, data->wall_img1);
	if (data->empty_img)
		mlx_destroy_image(data->mlx, data->empty_img);
	if (data->player_img)
		mlx_destroy_image(data->mlx, data->player_img);
	if (data->collect_img)
		mlx_destroy_image(data->mlx, data->collect_img);
	if (data->door_img)
		mlx_destroy_image(data->mlx, data->door_img);
	if (data->player_down[0])
		mlx_destroy_image(data->mlx, data->player_down[0]);
	if (data->player_down[1])
		mlx_destroy_image(data->mlx, data->player_down[1]);
	if (data->player_down[2])
		mlx_destroy_image(data->mlx, data->player_down[2]);
	if (data->player_down[3])
		mlx_destroy_image(data->mlx, data->player_down[3]);
	if (data->player_right[0])
		mlx_destroy_image(data->mlx, data->player_right[0]);
	if (data->player_right[1])
		mlx_destroy_image(data->mlx, data->player_right[1]);
	free_images2(data);
}

void	free_minilbx(t_info *data)
{
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(&data);
	free(data);
}
