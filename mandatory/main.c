/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/28 10:00:50 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_player_collect_enemy(t_info *data)
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
			if (data->map[k][i] == 'A')
			{
				data->e_nmb[data->e_index].e_x = k;
				data->e_nmb[data->e_index].e_y = i;


				//data->e_nmb[data->e_index].moves = 0; // caused a

					mlx_loop_hook(data->mlx, render_enemy, data);
				data->e_index++;
			}
			if (data->map[k][i] == 'E')
			{
				data->door_x = k;
				data->door_y = i;
				data->map[k][i] = '0';
			}
			i++;
		}
		k++;
	}
	data->enemy_nmb = data->e_index;

	//mlx_loop_hook(data->mlx, render_enemy, data);
}

void change_pos_collect(t_info *data, int keycode)
{
	data->previous_x = data->player_x;
	data->previous_y = data->player_y;
	press_keys(data, keycode);
	print_moves(data, data->previous_x, data->previous_y);
	collect_coins(data);
	if (data->collect == 0)
	{
		data->map[data->door_x][data->door_y] = 'E';
		mlx_put_image_to_window(data->mlx, data->win, data->door_img,
								data->door_y * 60, data->door_x * 60);
	}
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

int wall_enemy_coin(char c)
{
	if (c != '1' && c != 'C' && c != 'A' && c != 'E')
		return (1);
	return (0);
}

void idle_animation(t_info *data)
{
	if (data->e_index == data->enemy_nmb)
		data->e_index = 0;
	data->e_ani += 1;
}

void choose_direction(t_info *data) // data->e_index is within the bounds of data->e_nmb.
{
	// printf("e X : %d\n", data->e_nmb[data->e_index].e_y - 1);
	// printf("E Y : %d\n", data->e_nmb[data->e_index].e_y + 1);
	if  (!wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x][data->e_nmb[data->e_index].e_y - 1]) && !wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x][data->e_nmb[data->e_index].e_y + 1]))
	{
		mlx_put_image_to_window(data->mlx, data->win, data->enemy[data->e_ani], data->e_nmb[data->e_index].e_y * data->width, data->e_nmb[data->e_index].e_x * data->height);
	}
	else if (wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x][data->e_nmb[data->e_index].e_y - 1]) || wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x][data->e_nmb[data->e_index].e_y + 1]))
	{
		if (data->e_nmb[data->e_index].moves)
		{
			data->e_nmb[data->e_index].e_y++;
			// printf("creament Y  : %d\n", data->e_nmb[data->e_index].e_y);
		}
		else
		{
			data->e_nmb[data->e_index].e_y--;
			// printf("decremnt Y  : %d\n", data->e_nmb[data->e_index].e_y);

		}

		// printf("move move  : %d\n\n\n", data->e_nmb[data->e_index].moves);

		data->map[data->e_nmb[data->e_index].pre_x][data->e_nmb[data->e_index].pre_y] = '0';
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img, data->e_nmb[data->e_index].pre_y * data->width, data->e_nmb[data->e_index].pre_x * data->height);
		mlx_put_image_to_window(data->mlx, data->win, data->enemy[data->e_ani], data->e_nmb[data->e_index].e_y * data->width, data->e_nmb[data->e_index].e_x * data->height);
	}
}

void left_or_right(t_info *data)
{
	if (!wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x][data->e_nmb[data->e_index].e_y - 1]))
		data->e_nmb[data->e_index].moves = 1;
	else if (!wall_enemy_coin(data->map[data->e_nmb[data->e_index].e_x][data->e_nmb[data->e_index].e_y + 1]))
		data->e_nmb[data->e_index].moves = 0;
}

int render_enemy(t_info *data) // 2 enemy // data->enemy_nmb  = 2   \ = data->e_index = 2;
{
	idle_animation(data);
	if (data->e_ani == 5)
		data->e_ani = 0;
	data->e_nmb[data->e_index].pre_x = data->e_nmb[data->e_index].e_x;
	data->e_nmb[data->e_index].pre_y = data->e_nmb[data->e_index].e_y;

	left_or_right(data);
	choose_direction(data);
	left_or_right(data);
	touch_enemy(data);
	//usleep(70000); // enemy <= 3
	//usleep(40000);
	//usleep(100000);
	//usleep(20000); // enemy <= 6 7 8 9
	//usleep(14000);  // 11 12 13 14
	usleep(9000); // 16 17 18 19
	data->e_index++;
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
		// data->fire = mlx_xpm_file_to_image(data->mlx, "fire.xpm", &data->width, &data->height);
		draw_player_collect_enemy(data);
		mlx_key_hook(data->win, handle_key, data);
		// mlx_loop_hook(data->mlx, render_man, data);
		mlx_hook(data->win, 17, 0, cross_close, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error("Try: ./so_long  maps.ber 🚮");
	return (0);
}
