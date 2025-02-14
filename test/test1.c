
#include <fcntl.h>	// For open()
#include <stdlib.h> // For malloc()
#include <unistd.h> // For read()
#include <stdio.h>	// For printf()
#include <string.h> // For strlen()
#include "so_long.h"

// int main()
// {
// 	void *w;
// 	void *m = mlx_init();
// 	w = mlx_new_window(m, 100, 200, "hi");
// 	mlx_loop(m);
// }

// display one wall

// int main()
// {
//     void    *mlx;
//     void    *win;
//     void    *img;
//     int     img_width, img_height;

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, 800, 600, "So_Long");

//     // Load the image (replace "player.xpm" with your actual XPM file)
//     img = mlx_xpm_file_to_image(mlx, "Wall-Brick.xpm", &img_width, &img_height);

//     if (!img)
//         return (1); // Error handling: image not loaded

//     // Put the image at position (100, 100)
//     mlx_put_image_to_window(mlx, win, img, 1, 1);
//     mlx_loop(mlx); // Keep the window open
//     return (0);
// }


// move the player

// #define ESC 65307
// #define LEFT 65361
// #define RIGHT 65363
// #define UP 65362
// #define DOWN 65364

// typedef struct s_game
// {
// 	void *mlx;
// 	void *win;
// 	void *img;
// 	int x;
// 	int y;
// } t_game;

// int handle_key(int keycode, t_game *game)
// {
// 	if (!game) // Prevent null pointer access
// 		return (1);

// 	if (keycode == ESC)
// 	{
// 		mlx_destroy_window(game->mlx, game->win);
// 		return (0);
// 	}
// 	if (keycode == LEFT)
// 		game->x -= 60;
// 	if (keycode == RIGHT)
// 		game->x += 40;
// 	if (keycode == UP)
// 		game->y -= 10;
// 	if (keycode == DOWN)
// 		game->y += 10;

// 	// Clear window and redraw image at new position
// 	mlx_clear_window(game->mlx, game->win);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, game->x, game->y);

// 	return (0);
// }

// int main()
// {
// 	t_game *game;
// 	int img_w, img_h;

// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 		return (1);

// 	game->mlx = mlx_init();
// 	game->win = mlx_new_window(game->mlx, 800, 600, "Move Player");
// 	game->img = mlx_xpm_file_to_image(game->mlx, "player.xpm", &img_w, &img_h);
// 	game->x = 100;
// 	game->y = 100;

// 	mlx_put_image_to_window(game->mlx, game->win, game->img, game->x, game->y);
// 	mlx_key_hook(game->win, handle_key, game);

// 	mlx_loop(game->mlx);
// 	free(game);
// 	return (0);
// }

// #include <mlx.h>
// #include <fcntl.h>   // For open()
// #include <stdlib.h>  // For malloc()
// #include <unistd.h>  // For read()
// #include <stdio.h>   // For printf()
// #include <string.h>  // For strlen()

// // Structure to hold game data
// typedef struct s_game
// {
//     void    *mlx;
//     void    *win;
//     char    **map;
//     int     map_width;
//     int     map_height;
//     void    *wall_img;
//     void    *empty_img;
//     void    *player_img;
//     void    *collect_img;
//     void    *exit_img;
// } t_game;

// // Function to read the .ber file
// void read_map(t_game *game, char *filename)
// {
//     int     fd;
//     char    *line;
//     int     i = 0;

//     fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         printf("Error: Could not open map file\n");
//         return;
//     }

//     // Read number of lines to determine height
//     game->map_height = 0;
//     while ((line = get_next_line(fd))) // Use get_next_line to read file
//     {
//         game->map_height++;
//         free(line);
//     }
//     close(fd);

//     // Allocate memory for the map
//     game->map = malloc(sizeof(char *) * (game->map_height + 1));
//     if (!game->map)
//         return;

//     // Reopen file and read lines into the map array
//     fd = open(filename, O_RDONLY);
//     i = 0;
//     while ((line = get_next_line(fd)))
//     {
//         game->map[i] = line;
//         if (i == 0)
//             game->map_width = strlen(line) - 1; // Exclude newline
//         i++;
//     }
//     close(fd);
// }

// // Function to read the .ber file
// char **read_map(char *filename, int *map_width, int *map_height)
// {
//     int     fd;
//     char    **map;
//     char    *line;
//     int     i = 0;

//     fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         printf("Error: Could not open map file\n");
//         return (NULL);
//     }

//     // Read the number of lines to determine height
//     *map_height = 0;
//     while ((line = get_next_line(fd))) // You can use `gnl` (get_next_line)
//     {
//         (*map_height)++;
//         free(line);
//     }
//     close(fd);

//     // Allocate memory for the map
//     map = malloc(sizeof(char *) * (*map_height));
//     if (!map)
//         return (NULL);

//     // Reopen file and read lines into the map array
//     fd = open(filename, O_RDONLY);
//     i = 0;
//     while ((line = get_next_line(fd)))
//     {
//         map[i] = line;
//         if (i == 0)
//             *map_width = strlen(line) - 1; // Exclude newline character
//         i++;
//     }
//     close(fd);
//     return (map);
// }

// void draw_map(t_game *game)
// {
//     int x, y;

//     for (y = 0; y < game->map_height; y++)
//     {
//         for (x = 0; x < game->map_width; x++)
//         {
//             if (game->map[y][x] == '1') // Wall
//                 mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * WIDTH, y * HEIGHT);
//             else if (game->map[y][x] == '0') // Empty space
//                 mlx_put_image_to_window(game->mlx, game->win, game->empty_img, x * WIDTH, y * HEIGHT);
//             else if (game->map[y][x] == 'P') // Player
//                 mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * WIDTH, y * HEIGHT);
//             else if (game->map[y][x] == 'C') // Collectible
//                 mlx_put_image_to_window(game->mlx, game->win, game->collect_img, x * WIDTH, y * HEIGHT);
//             else if (game->map[y][x] == 'E') // Exit
//                 mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * WIDTH, y * HEIGHT);
//         }
//     }
// }

// int main()
// {
//     t_game *game;
// 	int w = WIDTH;
// 	int h = HEIGHT;
//     // Allocate memory for the game structure
//     game = malloc(sizeof(t_game));
//     if (!game)
//         return (1);

//     game->mlx = mlx_init();
// 	printf("%s \n", game->mlx );
//     read_map(game, "map.ber");

//     if (!game->map)
//         return (1); // Error handling

//     // game->win = mlx_new_window(game->mlx, game->map_width * WIDTH, game->map_height * HEIGHT, "So_Long");

//     // // Load images (assuming they exist as XPM files)
//     // game->wall_img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &w, &h);
//     // game->empty_img = mlx_xpm_file_to_image(game->mlx, "floor.xpm", &w, &h);
//     // game->player_img = mlx_xpm_file_to_image(game->mlx, "player.xpm", &w, &h);
//     // game->collect_img = mlx_xpm_file_to_image(game->mlx, "collect.xpm", &w, &h);
//     // game->exit_img = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &w, &h);
//     // draw_map(game);
//     // mlx_loop(game->mlx);
//     return (0);
// }
