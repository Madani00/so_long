/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:10:25 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 11:17:51 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initiaze_struct(t_info **data)
{
	(*data) = malloc(sizeof(t_info));
	(*data)->map = NULL;
	(*data)->c_map = NULL;
	(*data)->row = 0;
	(*data)->column = 0;
	(*data)->collect = 0;
	(*data)->player = 0;
	(*data)->exit = 0;
	(*data)->moves = 1;
	(*data)->animation = 0;
	(*data)->width = 60;
	(*data)->height = 60;
	(*data)->win = NULL;
	(*data)->e_index = 0;
	(*data)->e_ani = 0;
	(*data)->enemy_nmb = 0;
}

void get_mapsize(char **av, t_info **data)
{
	char *line;
	int fd;
	char *all_lines;

	fd = open(av[1], O_RDONLY);
	all_lines = NULL;
	line = get_next_line(fd);
	if (!line)
		free_error((*data), "Oops! This map is EMPTY haha  🚩 dummy 😓");
	(*data)->row = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if ((*data)->row != (ft_strlen(line) - 1))
		{
			free(all_lines);
			free(line);
			free_error((*data), "Oops! This map is invalid dummy 😓");
		}
		all_lines = join(all_lines, line);
		(*data)->column++;
		free(line);
		line = get_next_line(fd);
	}
	allocate_map(all_lines, data);
}

void allocate_map(char *all_lines, t_info **data)
{
	char **lines;
	int index;

	if ((*data)->column < 3 || (*data)->row < 3)
	{
		free(all_lines);
		free_error((*data), "Oops! This map is so small! 😓");
	}
	lines = ft_split(all_lines, '\n');
	free(all_lines);
	(*data)->map = malloc(sizeof(char *) * (*data)->column);
	(*data)->c_map = malloc(sizeof(char *) * (*data)->column);
	if (!(*data)->map || !(*data)->c_map)
		exit(EXIT_FAILURE);
	index = 0;
	while (index < (*data)->column)
	{
		(*data)->map[index] = ft_strdup(lines[index]);
		(*data)->c_map[index] = ft_strdup(lines[index]);
		index++;
	}
	free_args(lines);
}

int check_ones(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			i++;
		else
			return (0);
	}
	return (1);
}

void get_player_position(t_info **data, char *map_row, int index)
{
	int i;

	i = 0;
	while (i < (*data)->row)
	{
		if (map_row[i] == 'P')
		{
			(*data)->player_x = index;
			(*data)->player_y = i;
		}
		i++;
	}
}
