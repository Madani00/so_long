/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/12 12:18:08 by eamchart         ###   ########.fr       */
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
	printf("x : %d\n", (*data)->player_x);
	printf("y : %d\n", (*data)->player_y);
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
	//check_map_exetension(av[1]);
	initiaze_struct(data);
	get_mapsize(av, data);
	check_map_walls(data);
	flood_fill(data, (*data)->player_x, (*data)->player_y, "0PC", 'x');
	printf("-----copy-------\n");
	copy_map(data);
	printf("-----asly -------\n");
	asly(data);
	printf("PLAYER : %d\n", (*data)->player);
	printf("COLLECT : %d\n", (*data)->collect);
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
			jj++;
		}
		i++;
	}
	printf("EXIT : %d\n", (*data)->exit);
	if ((*data)->exit != 1)
		return (0);
	return (1);
}

int increment_components(char *targets, char pos, s_info **data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (targets[i] == pos)
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


void draw_map(s_info *game)
{
    int x, y;

    for (y = 0; y < game->column; y++)
    {
        for (x = 0; x < game->row; x++)
        {
            if (game->map[y][x] == '1') // Wall
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * WIDTH, y * HEIGHT);
            else if (game->map[y][x] == '0') // Empty space
                mlx_put_image_to_window(game->mlx, game->win, game->empty_img, x * WIDTH, y * HEIGHT);
            else if (game->map[y][x] == 'P') // Player
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * WIDTH, y * HEIGHT);
            else if (game->map[y][x] == 'C') // Collectible
                mlx_put_image_to_window(game->mlx, game->win, game->collect_img, x * WIDTH, y * HEIGHT);
            else if (game->map[y][x] == 'E') // Exit
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * WIDTH, y * HEIGHT);
        }
    }
}

int main(int ac, char *av[])
{
	int width = WIDTH;
	int height = HEIGHT;
    s_info *game;
	if (ac == 2)
		check_map_valid(av, &game);
    game->mlx = mlx_init();
	printf("Game structure initialized: %p\n", game);
	printf("MLX initialized: %p\n", game->mlx);
	printf("Map rows: %d, columns: %d\n", game->row, game->column);
    if (!game->map)
        return (1); // Error handling

    game->win = mlx_new_window(game->mlx, game->row * WIDTH, game->column * HEIGHT, "So_long");
	//game->img = mlx_xpm_file_to_image(game->mlx, "player.xpm", &width, &width);
	// mlx_put_image_to_window(game->mlx, game->win, game->img, game->player, game->player_y);
    // Load images (assuming they exist as XPM files)

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &width, &height);
	// mlx_put_image_to_window(game->mlx, game->win, game->wall_img, game->player, game->player_y);
    //game->empty_img = mlx_xpm_file_to_image(game->mlx, "floor.xpm", &WIDTH, &HEIGHT);
    //game->player_img = mlx_xpm_file_to_image(game->mlx, "player.xpm", &WIDTH, &HEIGHT);
    //game->collect_img = mlx_xpm_file_to_image(game->mlx, "collect.xpm", &WIDTH, &HEIGHT);
    //game->exit_img = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &WIDTH, &HEIGHT);

    //draw_map(game);
    mlx_loop(game->mlx);
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
