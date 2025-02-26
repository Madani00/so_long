/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/26 11:18:02 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_player_collect(t_info *data)
{
	int i;
	int k;
	int enemy_index;

	mlx_put_image_to_window(data->mlx, data->win, data->player_img,
							data->player_y * data->width, data->player_x * data->height);
	enemy_index = 0;
	k = 0;
	while (k < data->column)
	{
		i = 0;
		while (i < data->row)
		{
			if (data->map[k][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collect_img,
										i * data->width, k * data->height);
			if (data->map[k][i] == 'A')
			{
				data->enemy_nmb[enemy_index].enemy_x = k;
				data->enemy_nmb[enemy_index].enemy_y = i;
				mlx_loop_hook(data->mlx, render_enemy, data);
				enemy_index++;
			}
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
		mlx_put_image_to_window(data->mlx, data->win, data->fire,
								data->previous_y * 60, data->previous_x * 60); // mmm
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img,
								data->previous_y * 60, data->previous_x * 60);
	}
	moving_player(data, keycode);
	return (0);
}

int render_enemy(t_info *data)
{
	if (data->enemy_ani == 5)
		data->enemy_ani = 0;
	data->enemy_nmb[0].pre_x = data->enemy_nmb[0].enemy_x;
	data->enemy_nmb[0].pre_y = data->enemy_nmb[0].enemy_y;
	if (data->map[data->enemy_nmb[0].enemy_x][data->enemy_nmb[0].enemy_y - 1] != '1' || data->map[data->enemy_nmb[0].enemy_x][data->enemy_nmb[0].enemy_y + 1] != '1') // move enemy
	{
		if (data->enemy_nmb[0].moves)
			data->enemy_nmb[0].enemy_y++;
		else
			data->enemy_nmb[0].enemy_y--;
		data->map[data->enemy_nmb[0].pre_x][data->enemy_nmb[0].pre_y] = '0';
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img, data->enemy_nmb[0].pre_y * data->width, data->enemy_nmb[0].pre_x * data->height);
		mlx_put_image_to_window(data->mlx, data->win, data->enemy[data->enemy_ani], data->enemy_nmb[0].enemy_y * data->width, data->enemy_nmb[0].enemy_x * data->height);
	}

	if (data->map[data->enemy_nmb[0].enemy_x][data->enemy_nmb[0].enemy_y - 1] == '1')
		data->enemy_nmb[0].moves = 1;
	if (data->map[data->enemy_nmb[0].enemy_x][data->enemy_nmb[0].enemy_y + 1] == '1')
		data->enemy_nmb[0].moves = 0;

	if (data->enemy_nmb[0].enemy_x == data->player_x && data->enemy_nmb[0].enemy_y == data->player_y)
		exit(1);
	data->enemy_ani += 1;
	usleep(95000);
	return 0;
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
		load_enemy(data);
		draw_wall(data);
		data->fire = mlx_xpm_file_to_image(data->mlx, "fire.xpm", &data->width, &data->height);
		draw_player_collect(data);
		mlx_key_hook(data->win, handle_key, data);
		// mlx_loop_hook(data->mlx, render_man, data);
		mlx_hook(data->win, 17, 0, cross_close, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error("Try: ./so_long  maps.ber 🚮");
	return (0);
}
