/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:46:12 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/19 12:10:21 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_wall_helper(s_info *game, int *k, int *i)
{
	while (*i < game->row && *k % 2 == 0)
	{
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img, *i * game->width, *k * game->height);
		(*i)++;
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img1, *i * game->width, *k * game->height);
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

void draw_wall(s_info *game)
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

void reach_door_exit(s_info *data)
{
	if (data->map[data->player_x][data->player_y] == 'E' && data->collect == 0)
	{
		printf("You won!\n");
		mlx_destroy_image(data->mlx, data->wall_img);
		mlx_destroy_image(data->mlx, data->wall_img1);
		mlx_destroy_image(data->mlx, data->empty_img);

		mlx_destroy_image(data->mlx, data->player_img); // free 2
		mlx_destroy_image(data->mlx, data->collect_img);
		// if (data->player_img)
		// mlx_destroy_image(data->mlx, data->player_img);
		// mlx_destroy_window(data->mlx, data->exit_img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free_map(&data);
		free(data);
		exit(0);
	}
}
