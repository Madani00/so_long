/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:49:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/03/01 11:15:27 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*fetch_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

char	*allocation(int fd)
{
	char	*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ptr = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*get_next_line(int fd)
{
	ssize_t		readd;
	static char	*s_buffer;
	char		*file_data;
	char		*save;

	file_data = allocation(fd);
	if (!file_data)
		return (NULL);
	readd = 1;
	file_data[0] = '\0';
	while (readd > 0 && !ft_strchr(file_data, '\n'))
	{
		readd = read(fd, file_data, BUFFER_SIZE);
		if (readd < 0)
			return (free(file_data), free(s_buffer), s_buffer = NULL, NULL);
		file_data[readd] = '\0';
		s_buffer = join(s_buffer, file_data);
	}
	if (*s_buffer == '\0' && readd == 0)
		return (free(s_buffer), s_buffer = NULL, free(file_data), NULL);
	save = fetch_line(s_buffer);
	free(s_buffer);
	return (s_buffer = NULL, free(file_data), save);
}

char	*join(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

void	print_moves(t_info *data, int previous_x, int previous_y)
{
	char	*move;
	char	*s_move;
	int		position;

	move = ft_itoa(data->moves);
	s_move = ft_strjoin("Moves  :  ", move);
	position = data->column * data->height + 20;
	if ((data->player_x != previous_x && data->player_y == previous_y)
		|| (data->player_x == previous_x && data->player_y != previous_y))
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->empty_img, 60, position - 20);
		mlx_string_put(data->mlx, data->win, 20, position, 0xFF0000, s_move);
		ft_printf("%s \n", s_move);
		data->moves++;
	}
	free(move);
	free(s_move);
}
