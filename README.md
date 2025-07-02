
![Screencastfrom07-02-2025110058AM-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/7aac983f-0799-4eb7-b8ea-33a14f899ede)

## X WINDOW
- is a program that runs in the background on linux systems
- X uses a communication protocol to talk between the server and clients.
- how: it take commands and translates them to commands and it send to a client
- X client (application ): interact with the hardware on your machine
- The X server runs on your computer, and the clients can run either on the same machine or on a remote machine (over a network).
EXAMPLE : if i want to access a machine remotely and run an app that requires env to run then i can get to that machine to send me commands necessary to draw the pictures on my machine
- X clients connect to an X server, and they speak an X11 protocol, clients can send requests to ask the X server to do something. A simple example of a request is CreateWindow.  clients need to tell the X server which events they're interested in.
- MiniLibX internally uses XOpenDisplay() (Xlib function) to connect to the X server. / MiniLibX depends on Xlib (libX11, libXext)
`-lmlx` : This links the MiniLibX library (libmlx.a),
    It allows you to use functions like mlx_init(), mlx_new_window() ...

`-lX11` : links the X11 (X Window System) library, is a graphics system used on Linux to create windows and handle graphics.
It allows MiniLibX to interact with the graphical display.

`-lXext` : links the X Extensions library.
It provides additional features for X11, like handling images and special window properties.

## pixel bytes
- XPM is a simple, ASCII-based image format perfect for embedding or loading in MiniLibX.
- In MiniLibX, XPM images typically use 24 bpp (RGB) or 32 bpp (RGBA), which means each pixel holds 3 or 4 bytes.

## links
- canve webs to removes the background
https://www.remove.bg/
- flip the photos
https://pixlr.com/express/





