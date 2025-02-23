/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/23 09:14:24 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_player_collect(t_info *data)
{
	int i;
	int k;

	mlx_put_image_to_window(data->mlx, data->win, data->player_img,
							data->player_y * data->width, data->player_x * data->height);
	k = 0;
	while (k < data->column)
	{
		i = 0;
		while (i < data->row)
		{
			if (data->map[k][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collect_img,
										i * data->width, k * data->height);
			if (data->map[k][i] == 'E')
			{
				data->door_x = k;
				data->door_y = i;
			}
			i++;
		}
		k++;
	}
}

void change_pos_collect(t_info *data, int keycode)
{
	data->previous_x = data->player_x;
	data->previous_y = data->player_y;
	press_keys(data, keycode);
	print_moves(data, data->previous_x, data->previous_y);
	collect_coins(data);
	if (data->collect == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->door_img,
								data->door_y * 60, data->door_x * 60);
}

void moving_player(t_info *data, int keycode)
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

int handle_key(int keycode, t_info *data)
{
	if (keycode == ESC)
	{
		free_images(data);
		free_minilbx(data);
		exit(EXIT_SUCCESS);
	}
	change_pos_collect(data, keycode);
	reach_door_exit(data);
	if (data->direction != -1)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img,
								data->previous_y * 60, data->previous_x * 60);
	}
	moving_player(data, keycode);
	return (0);
}

int main(int ac, char *av[])
{
	t_info *data;

	if (ac == 2)
	{
		check_map_valid(av, &data);
		data->mlx = mlx_init();
		if (!data->mlx)
		{
			free_map(&data);
			free_error(data, "Oops! mlx_init failed 😓");
		}
		load_images(data);
		draw_wall(data);
		draw_player_collect(data);
		mlx_key_hook(data->win, handle_key, data);

		mlx_hook(data->win, 17, 0, cross_close, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error("Try: executable & maps.ber 🚮");
	return (0);
}
