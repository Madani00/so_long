/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:49:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/15 16:18:07 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#define BUFFER_SIZE 1

#define WIDTH 60
#define HEIGHT 60

#include <mlx.h>
#include "Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct map
{
	void *mlx;
	void *win;
	void *img;
	char **map;
	char **c_map;
	int row;
	int column;
	int collect;
	int player;
	int exit;
	int player_x;
	int player_y;
	void *wall_img;
	void *wall_img1;
	void *empty_img;
	void *player_img;
	void *collect_img;
	void *exit_img;
	int moves;
} s_info;

#define ESC 65307
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364

char *get_next_line(int fd);
char *allocation(int fd);
char *fetch_line(char *buffer);
char *join(char *s1, char *s2);

void check_map_content(s_info **data);
void allocate_map(char *all_lines, s_info **data);
void check_map_exetension(char *map_file);
void free_error(s_info *data, char *msg);
void free_args(char **arg);
void free_map(s_info **data);

void copy_map(s_info **data); // sdfdf
void asly(s_info **data);	  // kdf

void flood_fill(s_info **data, int x, int y, char *target, char replace);
int correct_components(s_info **data);
void initiaze_struct(s_info **data);
void get_mapsize(char **av, s_info **data);
void allocate_map(char *all_lines, s_info **data);
int check_ones(char *str);
void get_player_position(s_info **data, char *map_row, int index);
void draw_wall(s_info *game);
void draw_wall_helper(s_info *game, int *k, int *i);

#endif
