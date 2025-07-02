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
- X clients connect to an X server, and they speak an X11 protocol, clients can send requests to ask the X server to do something. A simple example of a request is CreateWindow.  clients need to tell the X server which events they're interested in.
- MiniLibX internally uses XOpenDisplay() (Xlib function) to connect to the X server. / MiniLibX depends on Xlib (libX11, libXext)

---
- to check which one used by your system
echo $XDG_SESSION_TYPE

- Idle Animations
when your player still moves without pressing anything


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


![Screencastfrom07-02-2025110058AM-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/7aac983f-0799-4eb7-b8ea-33a14f899ede)






