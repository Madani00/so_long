/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/18 10:20:00 by eamchart         ###   ########.fr       */
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

void draw_player_collect(s_info *data)
{
	int i;
	int k;

	mlx_put_image_to_window(data->mlx, data->win, data->player_img, data->player_y * WIDTH, data->player_x * HEIGHT);
	k = 0;
	while (k < data->column)
	{
		i = 0;
		while (i < data->row)
		{
			if (data->map[k][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collect_img, i * WIDTH, k * HEIGHT);
			if (data->map[k][i] == 'E' && data->exit_show)
				mlx_put_image_to_window(data->mlx, data->win, data->exit_img, i * WIDTH, k * HEIGHT);
			// if (data->map[k][i] == 'E')
			// {
			// 	data->door_x = k;
			// 	data->door_y = i;
			// }
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
	if ((keycode == LEFT || keycode == A) && data->map[data->player_x][data->player_y - 1] != '1')
	{
		data->direction = 3;
		data->player_y--;
	}
	if ((keycode == RIGHT ||keycode == D) && data->map[data->player_x][data->player_y + 1] != '1')
	{
		data->direction = 2;
		data->player_y++;
	}
	if ((keycode == UP || keycode == W) && data->map[data->player_x - 1][data->player_y] != '1')
	{
		data->direction = 1;
		data->player_x--;
	}
	if ((keycode == DOWN|| keycode == S) && data->map[data->player_x + 1][data->player_y] != '1')
	{
		data->direction = 0;
		data->player_x++;
	}
	if (data->collect == 0)
		data->exit_show = 1;
	print_moves(data, previous_x, previous_y);
	if (data->map[previous_x][previous_y] != '0')
	{
		if (data->map[previous_x][previous_y] == 'C')
			data->collect--;
		//data->map[previous_x][previous_y] = '0';
	}
}

int handle_key(int keycode, s_info *data)
{
	// if (!data)
	// 	return (1);
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free_map(&data);
		free(data);
		exit(0);
	}
	change_pos_collect(data, keycode);
	// if (data->collect == 0)
	// 	mlx_put_image_to_window(data->mlx, data->win, data->exit_img, data->door_y * WIDTH, data->door_x * HEIGHT);
	// if (data->collect == 0)
	// 		data->exit_show = 1;
	if (data->map[data->player_x][data->player_y] == 'E' && data->collect == 0)
	{
		printf("You won!\n");
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free_map(&data);
		free(data);
		exit(0);
	}
	//mlx_clear_window(data->mlx, data->win);
	//draw_wall(data);
	//draw_player_collect(data);
	mlx_put_image_to_window(data->mlx, data->win, data->empty_img , data->previous_y * WIDTH, data->previous_x * HEIGHT);
	mlx_put_image_to_window(data->mlx, data->win, data->player_img, data->player_y * WIDTH, data->player_x * HEIGHT);

	return (0);
}

// int loop_init(s_info *game)
// {
// 	if (game->exit_show)
// 		mlx_put_image_to_window(game->mlx, game->win, game->exit_img, game->door_y * WIDTH, game->door_x * HEIGHT);
// 	return (0);
// }

int main(int ac, char *av[])
{
	int width = WIDTH;
	int height = HEIGHT;
	s_info *data;
	if (ac == 2)
		check_map_valid(av, &data);
	data->mlx = mlx_init();

	if (data->row * WIDTH > 1920 || data->column * HEIGHT > 1080)
		return 1;
	data->win = mlx_new_window(data->mlx, data->row * WIDTH, data->column * HEIGHT, "So_long");
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./imgs/wall1.xpm", &width, &height);
	data->wall_img1 = mlx_xpm_file_to_image(data->mlx, "./imgs/wall2.xpm", &width, &height);
	data->empty_img = mlx_xpm_file_to_image(data->mlx, "./imgs/black.xpm", &width, &height);
	data->player_img = mlx_xpm_file_to_image(data->mlx, "./imgs/right/0.xpm", &width, &height);
	data->collect_img = mlx_xpm_file_to_image(data->mlx, "./imgs/coll.xpm", &width, &height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "./imgs/door.xpm", &width, &height);
	mlx_key_hook(data->win, handle_key, data);
	draw_wall(data);
	draw_player_collect(data);
	// if (data->collect == 0)
	// {
	// 	data->exit_img = mlx_xpm_file_to_image(data->mlx, "./imgs/door.xpm", &width, &height);
	// 	mlx_put_image_to_window(data->mlx, data->win, data->exit_img, data->player_y * WIDTH, data->player_x * HEIGHT);

	// }

	/*---------------------------------*/
	// mlx_loop_hook(data->mlx, loop_init, data);
	/*---------------------------------*/

	mlx_loop(data->mlx);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(&data);
	free(data);
	return (0);
}

// int main(int ac, char *av[])
// {
// 	s_info *data;

// 	if (ac == 2)
// 	{
// 		check_map_valid(av, &data);
// 	}
// 	else
// 		ft_error("Try: executable & maps.ber 🚮");
// 	return (0);
// }
