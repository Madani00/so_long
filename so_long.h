/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:49:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/08 14:52:33 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#define BUFFER_SIZE 1

#include "Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct map
{
	char **map;
	int row;
	int column;
	int collect;
	int player;
	int exit;
} s_info;

char *get_next_line(int fd);
char *allocation(int fd);
char *fetch_line(char *buffer);
char *join(char *s1, char *s2);

void check_map_content(s_info **data);
void allocate_map(char *all_lines, s_info **data);
void check_map_exetension(char *map_file);
void free_error(s_info *data, char *msg);
void	free_args(char **arg);
void	free_map(char **arg, int len);

#endif
