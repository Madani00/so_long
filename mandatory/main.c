/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/28 21:55:39 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player_collect_enemy(t_info *data)
{
	int	i;
	int	k;

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
			if_door_enemy(data, &k, &i);
			i++;
		}
		k++;
	}
	data->enemy_nmb = data->e_index;
	mlx_loop_hook(data->mlx, render_enemy, data);
}

void	change_pos_collect(t_info *data, int keycode)
{
	data->previous_x = data->player_x;
	data->previous_y = data->player_y;
	press_keys(data, keycode);
	if (data->map[data->player_x][data->player_y] == 'A')
	{
		free_images(data);
		free_minilbx(data);
		exit(EXIT_FAILURE);
	}
	print_moves(data, data->previous_x, data->previous_y);
	collect_coins(data);
	if (data->collect == 0)
	{
		data->map[data->door_x][data->door_y] = 'E';
		mlx_put_image_to_window(data->mlx, data->win, data->door_img,
			data->door_y * 60, data->door_x * 60);
	}
}

int	handle_key(int keycode, t_info *data)
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

int	render_enemy(t_info *data)
{
	idle_animation(data);
	if (data->e_ani == 5)
		data->e_ani = 0;
	while (data->e_index < data->enemy_nmb)
	{
		data->e_nmb[data->e_index].pre_x = data->e_nmb[data->e_index].e_x;
		data->e_nmb[data->e_index].pre_y = data->e_nmb[data->e_index].e_y;
		left_or_right(data);
		choose_direction(data);
		left_or_right(data);
		touch_enemy(data);
		usleep(210000 / data->enemy_nmb);
		data->e_index++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_info	*data;

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
		draw_player_collect_enemy(data);
		mlx_key_hook(data->win, handle_key, data);
		mlx_hook(data->win, 17, 0, cross_close, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error("Try: ./so_long  maps.ber 🚮");
	return (0);
}
