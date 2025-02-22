`-lmlx` : This links the MiniLibX library (libmlx.a),
    It allows you to use functions like mlx_init(), mlx_new_window() ...

`-lX11` : links the X11 (X Window System) library, is a graphics system used on Linux to create windows and handle graphics.
It allows MiniLibX to interact with the graphical display.

`-lXext` : links the X Extensions library.
It provides additional features for X11, like handling images and special window properties.


## links and beneficial

- canve webs to removes the background
https://www.remove.bg/


## invalid size read
- make sure to free them in the same order
mlx_destroy_window(data->mlx, data->win);
mlx_destroy_display(data->mlx);

# mast 1L << 0
- The mask is a bitwise filter that lets you fine-tune which events you want to capture. Each event in X11 has a corresponding mask.
