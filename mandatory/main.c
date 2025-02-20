/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/20 14:16:46 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


// int coin(void *param)
// {
// 	s_info *data = (s_info *)param;

// 	// Put the current frame's coin image at the correct position
// 	mlx_put_image_to_window(data->mlx, data->win, data->coins[data->frame], 2 * data->width, 2 * data->height);

// 	// Move to the next frame (loops between 0 and 3)
// 	data->frame = (data->frame + 1) % 4;

// 	return 0;
// }

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

void press_keys(s_info *data, int keycode)
{
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
}

void change_pos_collect(s_info *data, int keycode)
{
	int previous_x;
	int previous_y;

	previous_x = data->player_x;
	previous_y = data->player_y;
	data->previous_x = data->player_x;
	data->previous_y = data->player_y;
	press_keys(data, keycode);
	print_moves(data, previous_x, previous_y);
	if (data->map[previous_x][previous_y] == 'C')
		data->collect--;
	if (data->collect == 0)
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
		free_images(data);
		free_minilbx(data);
		exit(0);
	}
	change_pos_collect(data, keycode);
	reach_door_exit(data);
	if (data->direction != -1 || data->map[data->previous_x][data->previous_y] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->empty_img, data->previous_y * 60, data->previous_x * 60);
	moving_player(data, keycode);
	return (0);
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


// mistake if you step on the door
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
