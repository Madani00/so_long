/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:46:12 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/21 19:15:29 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void draw_wall_helper(t_info *game, int *k, int *i)
{
	while (*i < game->row && *k % 2 == 0)
	{
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
									*i * game->width, *k * game->height);
		(*i)++;
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img1,
									*i * game->width, *k * game->height);
		(*i)++;
	}
	while (*i < game->row && *k % 2 != 0)
	{
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img1, *i * game->width, *k * game->height);
		(*i)++;
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img, *i * game->width, *k * game->height);
		(*i)++;
	}
}

void draw_wall(t_info *game)
{
	int i;
	int k;

	k = 0;
	while (k < game->column)
	{
		i = 0;
		draw_wall_helper(game, &k, &i);
		k++;
	}
}

void reach_door_exit(t_info *data)
{
	if (data->map[data->player_x][data->player_y] == 'E' && data->collect == 0)
	{
		write(1, "You won!\n", 9);
		free_images(data);
		free_minilbx(data);
		exit(EXIT_SUCCESS);
	}
}

void check_map_walls(t_info **data)
{
	int i;

	if (!check_ones((*data)->map[0]) || !check_ones((*data)->map[(*data)->column - 1]))
	{
		free_map(data);
		free_error((*data), "Oops! This map is invalid dummy 😓");
	}
	i = 1;
	while (i < (*data)->column - 1)
	{
		if ((*data)->map[i][0] != '1' ||
			(*data)->map[i][(*data)->row - 1] != '1')
		{
			free_map(data);
			free_error((*data), "Oops! This map is invalid dummy 😓");
		}
		get_player_position(data, (*data)->map[i], i);
		i++;
	}
}

int correct_components(t_info **data)
{
	int i;
	int jj;

	if ((*data)->player != 1 || (*data)->collect == 0)
		return (0);
	i = 1;
	while (i < (*data)->column - 1)
	{
		jj = 1;
		while (jj < (*data)->row - 1)
		{
			if ((*data)->c_map[i][jj] == 'P' || (*data)->c_map[i][jj] == 'C')
				return (0);
			if ((*data)->c_map[i][jj] == 'E')
				(*data)->exit++;
			if ((*data)->c_map[i][jj] != 'x' && (*data)->c_map[i][jj] != 'E' && (*data)->c_map[i][jj] != '1' && (*data)->c_map[i][jj] != '0')
				return (0);
			jj++;
		}
		i++;
	}
	if ((*data)->exit != 1)
		return (0);
	return (1);
}
