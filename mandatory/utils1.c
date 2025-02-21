/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:10:25 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/21 12:12:18 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initiaze_struct(s_info **data)
{
	(*data) = malloc(sizeof(s_info));
	(*data)->map = NULL;
	(*data)->c_map = NULL;
	(*data)->row = 0;
	(*data)->column = 0;
	(*data)->collect = 0;
	(*data)->player = 0;
	(*data)->exit = 0;
	(*data)->moves = 0;
	(*data)->animation = 0;
	(*data)->width = 60;
	(*data)->height = 60;
	(*data)->frame = 0;
	(*data)->win = NULL;
}

void	get_mapsize(char **av, s_info **data)
{
	char	*line;
	int		fd;
	char	*all_lines;

	fd = open(av[1], O_RDONLY);
	all_lines = NULL;
	line = get_next_line(fd);
	if (!line)
		free_error((*data), "Oops! This map is EMPTY 🚩 dummy 😓");
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
	allocate_map(all_lines, data);
}

void	allocate_map(char *all_lines, s_info **data)
{
	char	**lines;
	int		index;

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

int	check_ones(char *str)
{
	int	i;

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

void	get_player_position(s_info **data, char *map_row, int index)
{
	int	i;

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
