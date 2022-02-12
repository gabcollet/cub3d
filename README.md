# cub3d

# Presentation

The goal of this project was to create a basic first-person maze like the old Wolfenstein 3D, using raycasting.<br/>

<p align="center">
    <img img width="600" height="500" src="https://i.ibb.co/tq3Xcjs/screenshot.png">
</p>

**Features**<br/>

Mandatory part:
- A custom map can be create using a .cub file including :
  - Different wall textures that vary depending on which side the wall is facing (North, South, East, West).
  - Different floor and ceiling colors using RGB.
  - Doors and enemies position (X, Y).
  - The map file itself. (1 = wall, 0 = floor).
  - A player facing a direction (N, S, E, W)
- A 3D rendering of a map file.

Bonus part:
- Wall collisions.
- A minimap system.
- Doors which can open and close.
- Animated sprite (gun and enemies).
- Rotate the point of view with the mouse.
- Custom transparency.

# How to run it

**How to launch**

First clone the git repo:
```
git clone git@github.com:gabcollet/cub3d.git; cd cub3D;
```
Then make and launch using a map file in "./maps/<mapfile>.cub"
Mac mandatory :
```
make; ./cub3D maps/m_complex.cub
```
Mac bonus :
```
make bonus; ./cub3D maps/b_complex.cub
```
Linux : (Dont forget to change keys in the include file)
```
make linux; ./cub3D maps/m_complex.cub
```
Linux bonus :
```
make b_linux; ./cub3D maps/b_complex.cub
```

**Command**

(On peux faire un tableau ici pour rendre ca plus clair)
-The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
-The W, A, S, and D keys must allow you to move the point of view through
the maze.
-Pressing ESC must close the window and quit the program cleanly.
-Clicking on the red cross on the window’s frame must close the window and
quit the program cleanly.
-E to interact with doors
-Space to shoot
-Shift to jump (at your own risk : buggy)

Key must be change between mac or linux in includes/cub3d.h or includes/cub3d_bonus.h

# Development process


  
<a href="https://imgbb.com/"><img img width="300" height="300" src="https://i.ibb.co/fSqkSjS/1.png" alt="1" border="0"></a><br/>
<a href="https://ibb.co/vwW6qcL"><img src="https://i.ibb.co/HFyf4KG/3.png" alt="3" border="0"></a><br/>
<a href="https://ibb.co/pWRGfbc"><img src="https://i.ibb.co/9wVzbc6/4.png" alt="4" border="0"></a><br/>
<a href="https://gifyu.com/image/SzuFG"><img img width="640" height="300" src="https://s10.gifyu.com/images/5589dafaba77a99b0.gif" alt="5589dafaba77a99b0.gif" border="0" /></a><br/>
<a href="https://ibb.co/6wHQQ6S"><img src="https://i.ibb.co/qjN66b8/6.png" alt="6" border="0"></a><br/>
<a href="https://ibb.co/pdfQDFp"><img src="https://i.ibb.co/7KnQcmF/7.png" alt="7" border="0"></a><br/>
<a href="https://gifyu.com/image/SzuF1"><img width="640" height="300" src="https://s10.gifyu.com/images/9c46c8d48067558f3.gif" alt="9c46c8d48067558f3.gif" border="0" /></a><br/>
<a href="https://gifyu.com/image/SzuFO"><img width="640" height="300" src="https://s10.gifyu.com/images/11e9a6cc7adb451779.gif" alt="11e9a6cc7adb451779.gif" border="0" /></a><br/>

# Ressources

- <a href="http://users.atw.hu/wolf3d/">Original Wolfenstein 3D game</a> 
- <a href="https://lodev.org/cgtutor/raycasting.html">Raytracing tutorial</a>
- <a href="https://github.com/qst0/ft_libgfx">X11 Event number</a>
- <a href="https://harm-smits.github.io/42docs/libs/minilibx">MinilibX 42 Docs</a>
- <a href="https://www.calculat.org/fr/aire-perimetre/triangle-rectangle.html">Right Triangle calculator</a>
- <a href="https://www.youtube.com/watch?v=eOCQfxRQ2pY">Wolfenstein 3D's map renderer video</a>
- <a href="https://www.youtube.com/watch?v=vYgIKn7iDH8">Rendering raycasting video</a>
- <a href="https://www.youtube.com/watch?v=NbSee-XM7WA&t=1393s">Super Fast Ray Casting in Tiled Worlds using DDA</a>
