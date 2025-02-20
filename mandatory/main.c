/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/20 12:07:27 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_map_walls(s_info **data)
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
		if ((*data)->map[i][0] != '1' || (*data)->map[i][(*data)->row - 1] != '1')
		{
			free_map(data);
			free_error((*data), "Oops! This map is invalid dummy 😓");
		}
		get_player_position(data, (*data)->map[i], i);
		i++;
	}
}

void asly(s_info **data)
{
	int i = 0;
	while (i < (*data)->column)
	{
		printf("%s\n", (*data)->map[i]);
		i++;
	}
}

void copy_map(s_info **data)
{
	int i = 0;
	while (i < (*data)->column)
	{
		printf("%s\n", (*data)->c_map[i]);
		i++;
	}
}

void check_map_valid(char **av, s_info **data)
{
	check_map_exetension(av[1]);
	initiaze_struct(data);
	get_mapsize(av, data);
	check_map_walls(data);
	flood_fill(data, (*data)->player_x, (*data)->player_y, "0PC", 'x');
	// copy_map(data);
	// asly(data);
	if (!correct_components(data))
	{
		free_map(data);
		free_error((*data), "Oops! Number of map's components INVALID 😓");
	}
}

int correct_components(s_info **data)
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

int increment_components(char *targets, char pos, s_info **data)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (targets[i] == pos) // 0PC
		{
			if (targets[i] == 'P')
				(*data)->player++;
			else if (targets[i] == 'C')
				(*data)->collect++;
			return (0);
		}
		i++;
	}
	return (1);
}

void flood_fill(s_info **data, int x, int y, char *target, char replace)
{
	if (x < 0 || x >= (*data)->column || y < 0 || y >= (*data)->row)
		return;
	if (increment_components(target, (*data)->c_map[x][y], data))
		return;
	if ((*data)->c_map[x][y] == replace)
		return;
	(*data)->c_map[x][y] = replace;
	flood_fill(data, x + 1, y, target, replace);
	flood_fill(data, x - 1, y, target, replace);
	flood_fill(data, x, y + 1, target, replace);
	flood_fill(data, x, y - 1, target, replace);
	return;
}

int coin(void *param)
{
	s_info *data = (s_info *)param;

	// Put the current frame's coin image at the correct position
	mlx_put_image_to_window(data->mlx, data->win, data->coins[data->frame], 2 * data->width, 2 * data->height);

	// Move to the next frame (loops between 0 and 3)
	data->frame = (data->frame + 1) % 4;

	return 0;
}

void draw_player_collect(s_info *data)
{
	int i;
	int k;

	mlx_put_image_to_window(data->mlx, data->win, data->player_img, data->player_y * data->width, data->player_x * data->height);
	k = 0;
	while (k < data->column)
	{
		i = 0;
		while (i < data->row)
		{
			if (data->map[k][i] == 'C')
				//mlx_loop_hook(data->mlx, coin, data);
				mlx_put_image_to_window(data->mlx, data->win, data->collect_img, i * data->width, k * data->height);
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

void print_moves(s_info *data, int previous_x, int previous_y)
{
	char *nmb;
	nmb = ft_itoa(data->moves);
	if (data->player_x != previous_x && data->player_y == previous_y)
	{
		write(1, "moves : ", 8);
		write(1, nmb, ft_strlen(nmb));
		write(1, "\n", 1);
		free(nmb);
		data->moves++;
	}
	else if (data->player_x == previous_x && data->player_y != previous_y)
	{
		write(1, "moves : ", 8);
		write(1, nmb, ft_strlen(nmb));
		write(1, "\n", 1);
		free(nmb);
		data->moves++;
	}
}

void change_pos_collect(s_info *data, int keycode)
{
	int previous_x;
	int previous_y;

	previous_x = data->player_x;
	previous_y = data->player_y;
	data->previous_x = data->player_x;
	data->previous_y = data->player_y;
	if ((keycode == A) && data->map[data->player_x][data->player_y - 1] != '1')
	{
		data->direction = 3;
		data->player_y--;
	}
	else if ((keycode == D) && data->map[data->player_x][data->player_y + 1] != '1')
	{
		data->direction = 2;
		data->player_y++;
	}
	else if ((keycode == W) && data->map[data->player_x - 1][data->player_y] != '1')
	{
		data->direction = 1;
		data->player_x--;
	}
	else if ((keycode == S) && data->map[data->player_x + 1][data->player_y] != '1')
	{
		data->direction = 0;
		data->player_x++;
	}
	else
	{
		data->direction = -1;
	}
	print_moves(data, previous_x, previous_y);
	if (data->map[previous_x][previous_y] == 'C')
		data->collect--;
	if (data->collect == 1)
		mlx_put_image_to_window(data->mlx, data->win, data->door_img, data->door_y * 60, data->door_x * 60);
}

void moving_player(s_info *data, int keycode)
{
	data->animation += 1;
	if (data->animation == 4)
		data->animation = 0;

	if (keycode == 'w')
		mlx_put_image_to_window(data->mlx, data->win, data->player_up[data->animation], data->player_y * data->width, data->player_x * data->height);
	else if (keycode == 'd')
		mlx_put_image_to_window(data->mlx, data->win, data->player_right[data->animation], data->player_y * data->width, data->player_x * data->height);
	else if (keycode == 'a')
		mlx_put_image_to_window(data->mlx, data->win, data->player_left[data->animation], data->player_y * data->width, data->player_x * data->height);
	else if (keycode == 's')
		mlx_put_image_to_window(data->mlx, data->win, data->player_down[data->animation], data->player_y * data->width, data->player_x * data->height);

}


int handle_key(int keycode, s_info *data)
{
	// if (!data)
	// 	return (1);
	if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx, data->wall_img);
		mlx_destroy_image(data->mlx, data->wall_img1);
		mlx_destroy_image(data->mlx, data->empty_img);
		mlx_destroy_image(data->mlx, data->player_img);
		mlx_destroy_image(data->mlx, data->collect_img);
		mlx_destroy_image(data->mlx, data->door_img);
		mlx_destroy_image(data->mlx, data->player_down[0]);
		mlx_destroy_image(data->mlx, data->player_down[1]);
		mlx_destroy_image(data->mlx, data->player_down[2]);
		mlx_destroy_image(data->mlx, data->player_down[3]);
		mlx_destroy_image(data->mlx, data->player_right[0]);
		mlx_destroy_image(data->mlx, data->player_right[1]);
		mlx_destroy_image(data->mlx, data->player_right[2]);
		mlx_destroy_image(data->mlx, data->player_right[3]);
		mlx_destroy_image(data->mlx, data->player_left[0]);
		mlx_destroy_image(data->mlx, data->player_left[1]);
		mlx_destroy_image(data->mlx, data->player_left[2]);
		mlx_destroy_image(data->mlx, data->player_left[3]);
		mlx_destroy_image(data->mlx, data->player_up[0]);
		mlx_destroy_image(data->mlx, data->player_up[1]);
		mlx_destroy_image(data->mlx, data->player_up[2]);
		mlx_destroy_image(data->mlx, data->player_up[3]);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free_map(&data);
		free(data);
		exit(0);
	}
	change_pos_collect(data, keycode);
	reach_door_exit(data);
	if (data->direction != -1)
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img, data->previous_y * 60, data->previous_x * 60);
	moving_player(data, keycode);
	return (0);
}

void load_images(s_info *data)
{
	data->win = mlx_new_window(data->mlx, data->row * data->width, data->column * data->height, "So_long");
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./imgs/wall1.xpm", &data->width, &data->height);
	data->wall_img1 = mlx_xpm_file_to_image(data->mlx, "./imgs/wall2.xpm", &data->width, &data->height);
	data->empty_img = mlx_xpm_file_to_image(data->mlx, "./imgs/black.xpm", &data->width, &data->height);
	data->player_img = mlx_xpm_file_to_image(data->mlx, "./imgs/down/0.xpm", &data->width, &data->height);
	data->collect_img = mlx_xpm_file_to_image(data->mlx, "./imgs/coll.xpm", &data->width, &data->height);
	data->door_img = mlx_xpm_file_to_image(data->mlx, "./imgs/door.xpm", &data->width, &data->height);

	data->player_down[0] = mlx_xpm_file_to_image(data->mlx, "./imgs/down/0.xpm", &data->width, &data->height);
	data->player_down[1] = mlx_xpm_file_to_image(data->mlx, "./imgs/down/1.xpm", &data->width, &data->height);
	data->player_down[2] = mlx_xpm_file_to_image(data->mlx, "./imgs/down/2.xpm", &data->width, &data->height);
	data->player_down[3] = mlx_xpm_file_to_image(data->mlx, "./imgs/down/3.xpm", &data->width, &data->height);
	data->player_right[0] = mlx_xpm_file_to_image(data->mlx, "./imgs/right/0.xpm", &data->width, &data->height);
	data->player_right[1] = mlx_xpm_file_to_image(data->mlx, "./imgs/right/1.xpm", &data->width, &data->height);
	data->player_right[2] = mlx_xpm_file_to_image(data->mlx, "./imgs/right/2.xpm", &data->width, &data->height);
	data->player_right[3] = mlx_xpm_file_to_image(data->mlx, "./imgs/right/3.xpm", &data->width, &data->height);
	data->player_left[0] = mlx_xpm_file_to_image(data->mlx, "./imgs/left/0.xpm", &data->width, &data->height);
	data->player_left[1] = mlx_xpm_file_to_image(data->mlx, "./imgs/left/1.xpm", &data->width, &data->height);
	data->player_left[2] = mlx_xpm_file_to_image(data->mlx, "./imgs/left/2.xpm", &data->width, &data->height);
	data->player_left[3] = mlx_xpm_file_to_image(data->mlx, "./imgs/left/3.xpm", &data->width, &data->height);
	data->player_up[0] = mlx_xpm_file_to_image(data->mlx, "./imgs/up/0.xpm", &data->width, &data->height);
	data->player_up[1] = mlx_xpm_file_to_image(data->mlx, "./imgs/up/1.xpm", &data->width, &data->height);
	data->player_up[2] = mlx_xpm_file_to_image(data->mlx, "./imgs/up/2.xpm", &data->width, &data->height);
	data->player_up[3] = mlx_xpm_file_to_image(data->mlx, "./imgs/up/3.xpm", &data->width, &data->height);
}

// void coin_animation(s_info *data)
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

int main(int ac, char *av[])
{
	s_info *data;

	if (ac == 2)
	{
		check_map_valid(av, &data);
		data->mlx = mlx_init();
		load_images(data);
		// mlx_key_hook(data->win, handle_key, data);
		draw_wall(data);
		//coin_animation(data);
		draw_player_collect(data);


		mlx_key_hook(data->win, handle_key, data);

		// mlx_loop_hook(data->mlx, coin, data);
		mlx_loop(data->mlx);
	}
	else
		ft_error("Try: executable & maps.ber 🚮");
	return (0);
}
