/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:46:12 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/13 18:46:45 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_wall_helper(s_info *game, int *k, int *i)
{
	while (*i < game->row && *k % 2 == 0)
	{
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img, *i * WIDTH, *k * HEIGHT);
		(*i)++;
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img1, *i * WIDTH, *k * HEIGHT);
		(*i)++;
	}
	while (*i < game->row && *k % 2 != 0)
	{
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img1, *i * WIDTH, *k * HEIGHT);
		(*i)++;
		if (game->map[*k][*i] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall_img, *i * WIDTH, *k * HEIGHT);
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
