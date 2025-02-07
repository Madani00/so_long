/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:49:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/07 10:33:17 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# define BUFFER_SIZE 1

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct map
{
	char **map;
	int row;
	int column;
} s_info;

char	*get_next_line(int fd);
char	*allocation(int fd);
char	*fetch_line(char *buffer);
char	*join(char *s1, char *s2);

#endif
