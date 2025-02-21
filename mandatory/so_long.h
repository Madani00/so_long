/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:49:39 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/21 18:06:01 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE 1

# include "../Libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct map
{
	void	*mlx;
	void	*win;
	void	*img;
	char	**map;
	char	**c_map;
	int		row;
	int		column;
	int		collect;
	int		player;
	int		exit;
	int		player_x;
	int		player_y;
	void	*wall_img;
	void	*wall_img1;
	void	*empty_img;
	void	*player_img;
	void	*collect_img;
	void	*door_img;
	int		moves;
	int		door_x;
	int		door_y;
	int		direction;
	void	*player_right[4];
	void	*player_left[4];
	void	*player_up[4];
	void	*player_down[4];
	int		previous_x;
	int		previous_y;
	int		animation;
	int		width;
	int		height;
	void	*coins[4];
	int		frame;
}			s_info;

# define ESC 65307

# define A 97
# define D 100
# define W 119
# define S 115

char		*get_next_line(int fd);
char		*allocation(int fd);
char		*fetch_line(char *buffer);
char		*join(char *s1, char *s2);
void		check_map_content(s_info **data);
void		allocate_map(char *all_lines, s_info **data);
void		check_map_exetension(char *map_file);
void		free_error(s_info *data, char *msg);
void		free_args(char **arg);
void		free_map(s_info **data);
void		flood_fill(s_info **data, int x, int y, char *target);
int			correct_components(s_info **data);
void		initiaze_struct(s_info **data);
void		get_mapsize(char **av, s_info **data);
void		allocate_map(char *all_lines, s_info **data);
int			check_ones(char *str);
void		get_player_position(s_info **data, char *map_row, int index);
void		draw_wall(s_info *game);
void		draw_wall_helper(s_info *game, int *k, int *i);
void		reach_door_exit(s_info *data);
void		free_images(s_info *data);
void		free_minilbx(s_info *data);
void		check_map_walls(s_info **data);
void		load_images(s_info *data);
void		check_map_valid(char **av, s_info **data);
int			increment_components(char *targets, char pos, s_info **data);
void		print_moves(s_info *data, int previous_x, int previous_y);
void		press_keys(s_info *data, int key);
void		collect_coins(s_info *data);
void		load_images2(s_info *data);
void		mlx_window_fail(s_info *data);
void		free_images2(s_info *data);

#endif
