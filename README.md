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

# flip the photos
https://pixlr.com/express/

- compile with
-lmlx -lX11 -lXext -lm

# pixel bytes
- XPM is a simple, ASCII-based image format perfect for embedding or loading in MiniLibX.
- In MiniLibX, XPM images typically use 24 bpp (RGB) or 32 bpp (RGBA), which means each pixel holds 3 or 4 bytes.

# X WINDOW
- is a program that runs in the background on linux systems
- X uses a communication protocol to talk between the server and clients.
- how: it take commands and translates them to commands and it send to a client
- X client (application ): interact with the hardware on your machine
- The X server runs on your computer, and the clients can run either on the same machine or on a remote machine (over a network).
EXAMPLE : if i want to access a machine remotely and run an app that requires env to run then i can get to that machine to send me commands necessary to draw the pictures on my machine



---
- to check which one used by your system
echo $XDG_SESSION_TYPE

- Idle Animations
when your player still moves without pressing anything


Final Effect

✔️ Press Left → Player moves left + animated movement frames
✔️ Press Nothing → Player stays in place but has a small "idle effect"
✔️ Press Right → Player moves right with animation


//  int moving; 1 = moving, 0 = idle

int render_player(s_info *data)
{
    if (data->player.moving)
        data->player.frame = (data->player.frame + 1) % 4; // Change frame for movement
    else
        data->player.frame = (data->player.frame + 1) % 2; // Smaller animation for idle

    mlx_put_image_to_window(data->mlx, data->win,
        data->player.sprites[data->player.direction][data->player.frame],
        data->player.x * TILE_SIZE, data->player.y * TILE_SIZE);
    return (0);
}

1 - Erase the old enemy position – Instead of redrawing everything, just redraw the tile that was underneath the enemy (like the floor or background). This ensures the old enemy sprite is removed cleanly.
2 - Update the enemy's position – Change the enemy’s coordinates based on its movement logic. If the enemy moves left or right, update its X position. If it moves up or down, update its Y position.
3 - Draw the enemy at the new position – After updating the position, draw the enemy sprite in the new location.
4 - Handle movement boundaries – If the enemy reaches a certain limit (like a wall or a max distance), make it change direction or stop moving.

---

```bash
typedef struct enemy
{
	int e_x;
	int e_y;
	int moves;
	int pre_x;
	int pre_y;
} t_enemy;

t_enemy e_nmb[1000];
```
- declares an array named e_nmb that can hold 1000 instances of the t_enemy structure.
- 1000 bytes = 1 KB
---
- how to calculate how many bytes in the photo:
 60 * 60 pixels = 3600 pixels
 3600 * 4 bytes or 3 bytes =
---
- subject : `*.ber` so means a file with `.ber` is invalid cause `*` says it must be something , about the `..ber ` is bullshit
---
- this one should not segfault
`valgrind so_long/so_long so_long/maps/map6.ber`
---
-  **Esc + Enter** in the terminal `zsh` can cause the shell or program to wait for more input,
