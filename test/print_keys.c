// press ESC KEY

#define ESC 65307  // Escape key in Linux

void close_window(void *mlx, void *win)
{
    mlx_destroy_window(mlx, win);
    printf("Window closed.\n");
}
int handle_key(int keycode, void *param)
{
    if (keycode == ESC) // Close window when ESC is pressed
    {
        close_window(param, param);
    }
    else
    {
        printf("Key pressed: %d\n", keycode);
    }
    return (0);
}
int main()
{
    void *mlx;
    void *win;
    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Keyboard Handling");

    // Hook keyboard event
    mlx_key_hook(win, handle_key, mlx);

    mlx_loop(mlx);
    return (0);
}
