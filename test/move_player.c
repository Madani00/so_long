

#define ESC 65307
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    int     x;
    int     y;
} t_game;

int handle_key(int keycode, t_game *game)
{
	 if (!game) // Prevent null pointer access (this was my problem)
        return (1);

    if (keycode == ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        return (0);
    }
    if (keycode == LEFT)  game->x -= 60;
    if (keycode == RIGHT) game->x += 40;
    if (keycode == UP)    game->y -= 10;
    if (keycode == DOWN)  game->y += 10;

    // Clear window and redraw image at new position
    mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->img, game->x, game->y);

    return (0);
}

int main()
{
    t_game *game;
	int img_w, img_h;

	game = malloc(sizeof(t_game));
    if (!game)
        return (1);

    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 800, 600, "Move Player");
    game->img = mlx_xpm_file_to_image(game->mlx, "player.xpm", &img_w, &img_h);
    game->x = 100;
    game->y = 100;

    mlx_put_image_to_window(game->mlx, game->win, game->img, game->x, game->y);
    mlx_key_hook(game->win, handle_key, game);

    mlx_loop(game->mlx);
	free(game);
    return (0);
}
