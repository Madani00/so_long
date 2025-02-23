/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/23 12:58:20 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

// int coin(void *param)
// {
// 	t_info *data = (t_info *)param;

// 	// Put the current frame's coin image at the correct position
// 	mlx_put_image_to_window(data->mlx, data->win, data->coins[data->frame], 2 * data->width, 2 * data->height);

// 	// Move to the next frame (loops between 0 and 3)
// 	data->frame = (data->frame + 1) % 4;

// 	return (0);
// }

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
				// mlx_loop_hook(data->mlx, coin, data);
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
	// if (!data)
	// 	return (1);
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

// void coin_animation(t_info *data)
// {
// 	data->coins[0] = mlx_xpm_file_to_image(data->mlx, "./imgs/coll.xpm", &data->width, &data->height);
// 	data->coins[1] = mlx_xpm_file_to_image(data->mlx, "./imgs/coll22.xpm", &data->width, &data->height);
// 	data->coins[2] = mlx_xpm_file_to_image(data->mlx, "./imgs/coll.xpm", &data->width, &data->height);
// 	data->coins[3] = mlx_xpm_file_to_image(data->mlx, "./imgs/coll22.xpm", &data->width, &data->height);
// 	// mlx_put_image_to_window(data->mlx, data->win, data->coins[data->frame], 2 * data->width, 2 * data->height);
// 	// data->frame = (data->frame + 1) % 4;
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (!data->coins[i])
// 		{
// 			printf("Error: Failed to load coin image %d\n", i);
// 			exit(1);
// 		}
// 	}
// }

void  load_enemy(t_info *data)
{
	data->enemy[0] = mlx_xpm_file_to_image(data->mlx,
										   "./imgs/enemy/0.xpm", &data->width, &data->height);
	data->enemy[1]= mlx_xpm_file_to_image(data->mlx,
												 "./imgs/enemy/1.xpm", &data->width, &data->height);
	data->enemy[2] = mlx_xpm_file_to_image(data->mlx,
												 "./imgs/enemy/2.xpm", &data->width, &data->height);
	data->enemy[3] = mlx_xpm_file_to_image(data->mlx,
												 "./imgs/enemy/3.xpm", &data->width, &data->height);
	data->enemy[4] = mlx_xpm_file_to_image(data->mlx,
												 "./imgs/enemy/4.xpm", &data->width, &data->height);
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
		// mlx_key_hook(data->win, handle_key, data);
		draw_wall(data);
		// coin_animation(data);
		draw_player_collect(data);
		mlx_key_hook(data->win, handle_key, data);
		// mlx_hook(data->win, 2, 0, handle_key, data);
		// mlx_loop_hook(data->mlx, coin, data);
		mlx_hook(data->win, 17, 0, cross_close, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error("Try: executable & maps.ber 🚮");
	return (0);
}
