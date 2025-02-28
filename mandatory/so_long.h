/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:49:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/27 14:32:51 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#define BUFFER_SIZE 1

#include "../Libft/libft.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct enemy
{
	int e_x;
	int e_y;
	int moves;
	int pre_x;
	int pre_y;
} t_enemy;

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
	void *door_img;
	int door_x;
	int door_y;
	int direction;
	void *player_right[4];
	void *player_left[4];
	void *player_up[4];
	void *player_down[4];
	int previous_x;
	int previous_y;
	int moves;
	int animation;
	int width;
	int height;
	// void *effect;
	void *enemy[5];
	int e_ani;
	t_enemy e_nmb[100];
	int e_index;
	int enemy_nmb;
} t_info;

#define ESC 65307
#define A 97
#define D 100
#define W 119
#define S 115

char *get_next_line(int fd);
char *allocation(int fd);
char *fetch_line(char *buffer);
char *join(char *s1, char *s2);
void check_map_content(t_info **data);
void allocate_map(char *all_lines, t_info **data);
void check_map_exetension(char *map_file);
void free_error(t_info *data, char *msg);
void free_args(char **arg);
void free_map(t_info **data);
void flood_fill(t_info **data, int x, int y, char *target);
int correct_components(t_info **data);
void initiaze_struct(t_info **data);
void get_mapsize(char **av, t_info **data);
void allocate_map(char *all_lines, t_info **data);
int check_ones(char *str);
void get_player_position(t_info **data, char *map_row, int index);
void draw_wall(t_info *game);
void draw_wall_helper(t_info *game, int *k, int *i);
void reach_door_exit(t_info *data);
void free_images(t_info *data);
void free_minilbx(t_info *data);
void check_map_walls(t_info **data);
void load_images(t_info *data);
void check_map_valid(char **av, t_info **data);
int increment_components(char *targets, char pos, t_info **data);
void print_moves(t_info *data, int previous_x, int previous_y);
void press_keys(t_info *data, int key);
void collect_coins(t_info *data);
void load_images2(t_info *data);
void mlx_window_fail(t_info *data);
void free_images2(t_info *data);
int cross_close(t_info *data);
void  load_enemy(t_info *data);
int render_enemy(t_info *data);
int wall_enemy_coin(char c);
void window_size_error(t_info *data);
void free_images3(t_info *data);
void touch_enemy(t_info *data);

#endif
