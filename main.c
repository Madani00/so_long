/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:51:19 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/07 11:25:13 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

s_info *initiaze_struct()
{
	s_info *data = malloc(sizeof(s_info));
	data->map = NULL;
	data->row = 0;
	data->column = 0;
	return (data);
}

void	free_all(s_info *data)
{
	free(data);
}

void check_map(char *map_file)
{
	if (!(ft_strnstr(map_file, ".ber", ft_strlen(map_file))))
	{
		ft_error("Error\nInvalid map NAME dummy :(");
		exit(EXIT_FAILURE);
	}
}

int get_size(char **av)
{
	check_map(av[1]);
	s_info *data;
	data = initiaze_struct();
	char *line;
	int fd = open(av[1], O_RDONLY);
	int row = 0;

	line = get_next_line(fd);
	data->row = ft_strlen(line) - 1;
	printf("%d \n", data->row);
	while (line != NULL)
	{
		row = ft_strlen(line) - 1;
		if (data->row != row)
		{
			free(line);
			free_all(data);
			printf("error \n");
			exit(EXIT_FAILURE);
		}
		printf("%s", line);
		data->column++;
		free(line);
		line = get_next_line(fd);
	}
	free(data);
	//printf("%d \n", data->column);
	return 0;
}

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		return (get_size(av));
	}
	else
		ft_error("Error\nargument are more than");
	return (0);
}
