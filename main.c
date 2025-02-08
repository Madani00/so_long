/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/08 14:54:52 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initiaze_struct(s_info **data)
{
	(*data) = malloc(sizeof(s_info));
	(*data)->map = NULL;
	(*data)->row = 0;
	(*data)->column = 0;
	(*data)->collect = 0;
	(*data)->player = 0;
	(*data)->exit = 0;
}

void get_mapsize(char **av, s_info **data)
{
	char *line;
	int fd;
	char *all_lines;

	fd = open(av[1], O_RDONLY);
	all_lines = NULL;
	line = get_next_line(fd);
	if (!line)
		free_error((*data), "Oops! This map is invalid dummy 😓");
	(*data)->row = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if ((*data)->row != (ft_strlen(line) - 1))
		{
			free(all_lines);
			free(line);
			free_error((*data), "Oops! This map is invalid dummy 😓");
		}
		all_lines = ft_strjoin(all_lines, line);
		(*data)->column++;
		free(line);
		line = get_next_line(fd);
	}
	allocate_map(all_lines, data); // 24
}

void allocate_map(char *all_lines, s_info **data)
{
	char **lines;
	int index;

	if ((*data)->column < 3 || (*data)->row < 3)
	{
		free(all_lines);
		free_error((*data), "Oops! This map is so small, even 🐁 would get lost! 😓");
	}
	lines = ft_split(all_lines, '\n');
	free(all_lines);
	(*data)->map = malloc(sizeof(char *) * (*data)->column);
	if (!(*data)->map)
		exit(EXIT_FAILURE);
	index = 0;
	while (index < (*data)->column)
	{
		(*data)->map[index] = ft_strdup(lines[index]);
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

void check_map_walls(s_info **data)
{
	int i;

	i = 0;
	while (i < (*data)->column)
	{
		if (!check_ones((*data)->map[0]) || !check_ones((*data)->map[(*data)->column - 1]))
		{
			free_map((*data)->map, (*data)->column);
			free_error((*data), "tfooooo invalid dummy 😓");
		}
		if ((*data)->map[i][0] != '1' || (*data)->map[i][(*data)->row - 1] != '1')
		{
			free_map((*data)->map, (*data)->column);
			free_error((*data), "Oops! This map is invalid dummy 😓");
		}
		// printf(" map 222 --->  %s \n", (*data)->map[i]);
		i++;
	}
}

void check_map_valid(char **av, s_info **data)
{
	check_map_exetension(av[1]);
	initiaze_struct(data);
	get_mapsize(av, data);
	check_map_walls(data);
}

int main(int ac, char *av[])
{
	s_info *data;

	if (ac == 2)
	{
		check_map_valid(av, &data);
	}
	else
		ft_error("Try: executable & maps.ber 🚮");
	return (0);
}
