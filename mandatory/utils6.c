/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:23:33 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 15:09:43 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	choose_direction_helper(t_info *data, char elem1, char elem2)
{
	if (wall_enemy_coin(elem1) || wall_enemy_coin(elem2))
	{
		if (data->e_nmb[data->e_index].moves)
			data->e_nmb[data->e_index].e_y++;
		else
			data->e_nmb[data->e_index].e_y--;
		data->map[data->e_nmb[data->e_index].pre_x]
		[data->e_nmb[data->e_index].pre_y] = '0';
		data->map[data->e_nmb[data->e_index].e_x]
		[data->e_nmb[data->e_index].e_y] = 'A';
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img,
			data->e_nmb[data->e_index].pre_y * data->width,
			data->e_nmb[data->e_index].pre_x * data->height);
		mlx_put_image_to_window(data->mlx, data->win, data->enemy[data->e_ani],
			data->e_nmb[data->e_index].e_y * data->width,
			data->e_nmb[data->e_index].e_x * data->height);
	}
}

void	choose_direction(t_info *data)
{
	char	elem1;
	char	elem2;

	elem1 = data->map[data->e_nmb[data->e_index].e_x]
	[data->e_nmb[data->e_index].e_y - 1];
	elem2 = data->map[data->e_nmb[data->e_index].e_x]
	[data->e_nmb[data->e_index].e_y + 1];
	if (!wall_enemy_coin(elem1) && !wall_enemy_coin(elem2))
	{
		mlx_put_image_to_window(data->mlx, data->win, data->enemy[data->e_ani],
			data->e_nmb[data->e_index].e_y * data->width,
			data->e_nmb[data->e_index].e_x * data->height);
	}
	choose_direction_helper(data, elem1, elem2);
}

void	left_or_right(t_info *data)
{
	if (!wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x]
			[data->e_nmb[data->e_index].e_y - 1]))
		data->e_nmb[data->e_index].moves = 1;
	else if (!wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x]
			[data->e_nmb[data->e_index].e_y + 1]))
		data->e_nmb[data->e_index].moves = 0;
}

void	moving_player(t_info *data, int keycode)
{
	if (data->animation == 4)
		data->animation = 0;
	if (keycode == 'w')
		mlx_put_image_to_window(data->mlx, data->win,
			data->player_up[data->animation], data->player_y * data->width,
			data->player_x * data->height);
	else if (keycode == 'd')
		mlx_put_image_to_window(data->mlx, data->win,
			data->player_right[data->animation], data->player_y * data->width,
			data->player_x * data->height);
	else if (keycode == 'a')
		mlx_put_image_to_window(data->mlx, data->win,
			data->player_left[data->animation], data->player_y * data->width,
			data->player_x * data->height);
	else if (keycode == 's')
		mlx_put_image_to_window(data->mlx, data->win,
			data->player_down[data->animation], data->player_y * data->width,
			data->player_x * data->height);
	data->animation += 1;
}

void	check_all_map(t_info **data)
{
	int	k;
	int	i;

	k = 0;
	while (k < (*data)->column)
	{
		i = 0;
		while (i < (*data)->row)
		{
			if ((*data)->map[k][i] == 'x')
			{
				free_map(data);
				free_error((*data), "Ops! Number of map's component INVALID 😓");
			}
			i++;
		}
		k++;
	}
}
