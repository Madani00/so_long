#include <mlx.h>
#include <stdio.h>

typedef struct s_data {
    void *mlx;
    void *win;
    void *player[4];  // Array to store 4 animation frames
    int frame;
    int x;
} t_data;

int animate_player(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);

    // Draw the current frame of the player
    mlx_put_image_to_window(data->mlx, data->win, data->player[data->frame], data->x, 100);

    // Change frame (cycle 0 -> 1 -> 2 -> 3 -> 0 -> ...)
	data->frame++;
	if (data->frame == 4)
		data->frame = 0;

	return (0);
}

int main()
{
    t_data data;

	int width = 32;
	int height = 32;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 500, 500, "Player Animation");
    data.frame = 0;
    data.x = 100;

    // Load 4 animation frames
    data.player[0] = mlx_xpm_file_to_image(data.mlx, "down/0.xpm", &width, &height);
    data.player[1] = mlx_xpm_file_to_image(data.mlx, "down/1.xpm", &width, &height);
    data.player[2] = mlx_xpm_file_to_image(data.mlx, "down/2.xpm", &width, &height);
    data.player[3] = mlx_xpm_file_to_image(data.mlx, "down/3.xpm", &width, &height);

    mlx_loop_hook(data.mlx, animate_player, &data);
    mlx_loop(data.mlx);

    return (0);
}
