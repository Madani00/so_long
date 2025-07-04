/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:55:06 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 14:27:03 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_exetension(char *map_file)
{
	char	*start;

	start = &map_file[ft_strlen(map_file) - 4];
	if ((ft_strcmp(map_file, "maps/..ber") == 0)
		|| (ft_strcmp(map_file, "maps/.ber") == 0))
	{
		ft_error("Map not found dummy 🌍");
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(start, ".ber", 4) != 0))
	{
		ft_error("Map not found dummy 🌍");
		exit(EXIT_FAILURE);
	}
}

void	load_images(t_info *data)
{
	data->win = mlx_new_window(data->mlx, data->row * data->width,
			data->column * data->height + 32, "So_long");
	if (!data->win)
		mlx_window_fail(data);
	data->wall_img = mlx_xpm_file_to_image(data->mlx,
			"./imgs/wall1.xpm", &data->width, &data->height);
	data->wall_img1 = mlx_xpm_file_to_image(data->mlx,
			"./imgs/wall2.xpm", &data->width, &data->height);
	data->empty_img = mlx_xpm_file_to_image(data->mlx,
			"./imgs/black.xpm", &data->width, &data->height);
	data->player_img = mlx_xpm_file_to_image(data->mlx,
			"./imgs/down/0.xpm", &data->width, &data->height);
	data->collect_img = mlx_xpm_file_to_image(data->mlx,
			"./imgs/coll.xpm", &data->width, &data->height);
	data->door_img = mlx_xpm_file_to_image(data->mlx,
			"./imgs/door.xpm", &data->width, &data->height);
	data->player_down[0] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/down/0.xpm", &data->width, &data->height);
	data->player_down[1] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/down/1.xpm", &data->width, &data->height);
	data->player_down[2] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/down/2.xpm", &data->width, &data->height);
	data->player_down[3] = mlx_xpm_file_to_image(data->mlx,
			"./imgs/down/3.xpm", &data->width, &data->height);
	load_images2(data);
}

void	check_map_valid(char **av, t_info **data)
{
	check_map_exetension(av[1]);
	initiaze_struct(data);
	get_mapsize(av, data);
	check_map_walls(data);
	check_all_map(data);
	flood_fill(data, (*data)->player_x, (*data)->player_y, "0PECA");
	if (!correct_components(data))
	{
		free_map(data);
		free_error((*data), "Oops! Number of map's components INVALID 😓");
	}
	window_size_error(*data);
}

int	increment_components(char *targets, char pos, t_info **data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (targets[i] == pos)
		{
			if (targets[i] == 'P')
				(*data)->player++;
			else if (targets[i] == 'C')
				(*data)->collect++;
			else if (targets[i] == 'E')
				(*data)->exit++;
			return (0);
		}
		i++;
	}
	return (1);
}

void	flood_fill(t_info **data, int x, int y, char *target)
{
	if (x < 0 || x >= (*data)->column || y < 0 || y >= (*data)->row)
		return ;
	if (increment_components(target, (*data)->c_map[x][y], data))
		return ;
	(*data)->c_map[x][y] = 'x';
	flood_fill(data, x + 1, y, target);
	flood_fill(data, x - 1, y, target);
	flood_fill(data, x, y + 1, target);
	flood_fill(data, x, y - 1, target);
	return ;
}
