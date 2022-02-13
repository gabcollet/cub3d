# cub3d

##### Table of Contents  
[Presentation](#presentation)  
[How to run it](#how-to-run-it)  
[Commands](#commands)  
[Development process](#development-process)  
[Ressources](#ressources) 

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

First clone the git repo:
```
git clone git@github.com:gabcollet/cub3d.git; cd cub3D;
```
Then make and launch using a map file in "./maps/<mapfile>.cub"<br/>
Mac mandatory :
```
make; ./cub3D maps/m_complex.cub
```
Mac bonus :
```
make bonus; ./cub3D maps/b_complex.cub
```
Linux mandatory : (Dont forget to change keys in the include file)
```
make linux; ./cub3D maps/m_complex.cub
```
Linux bonus :
```
make b_linux; ./cub3D maps/b_complex.cub
```

# Commands

**Key must be change between mac or linux in includes/cub3d.h or includes/cub3d_bonus.h**

| Key           | Command       |
| ------------- |:-------------:|
| <-- or -->    | Look left and right |
| W, A, S, D    | Move      |
| ESC           | Quit      |
| E             | Open doors|
| Space bar     | Shoot     |
| Shift         | Jump      |
| M             | Toggle map|

# Development process

 - To begin we created the MLX windows.
 - Added movement using key pressed and released.
 - Added collision between the player and walls.
 - Raycasting :
    - First we've checked every intersection of the grid to see if the collision was with a wall.
    - Then we calculate for that distance.
    
<a href="https://imgbb.com/"><img width="200" height="200" src="https://i.ibb.co/9WrgmhX/Screenshot-from-2022-02-13-15-06-42.png" alt="Screenshot-from-2022-02-13-15-06-42" border="0"></a>
<a href="https://imgbb.com/"><img width="300" height="200" src="https://i.ibb.co/HYqh9Jy/Screenshot-from-2022-02-13-15-07-12.png" alt="Screenshot-from-2022-02-13-15-07-12" border="0"></a>
<a href="https://imgbb.com/"><img width="200" height="200" src="https://i.ibb.co/RyvqJGD/Screenshot-from-2022-02-13-15-09-43.png" alt="Screenshot-from-2022-02-13-15-09-43" border="0"></a><br/>
It gave us a function like that where _pos_ is the player position, _rot_ is the angle of the specific ray, _coll_ is the collision point with the wall and _angle_ is the rotation of the player minus the current ray rotation.
```C
double	get_draw_distance(t_pos pos, double rot, t_pos coll, double angle)
{
	double	d_x;
	double	d_y;
	double	sin_result;
	double	cos_result;
	double	dist;

	d_x = (int)fabs(pos.x - coll.x);
	d_y = (int)fabs(pos.y - coll.y);
	cos_result = fabs(cos(deg_to_rad((int)rot)));
	sin_result = fabs(sin(deg_to_rad((int)rot)));
	dist = d_x * cos_result + d_y * sin_result;
	dist = dist * cos((deg_to_rad((int)angle)));
	dist = (TILE_SIZE * g_game.res_h) / dist;
	return (dist);
}
```    
<a href="https://imgbb.com/"><img img width="300" height="300" src="https://i.ibb.co/fSqkSjS/1.png" alt="1" border="0"></a><br/>
    
 - Using the previously found distance we build the 3D rendering of the wall. Here's a part of the final function for a north wall. We can see that the function call for another _fill_with_texture_ function that calculate the step in between each pixel that needed to be put. 
 ```C
 int	draw3d(float height, t_coll coll, int x)
{
	int		y;
	float	offset;

	offset = 0;
	if (height > WIN_H)
	{
		offset = (height - WIN_H);
		height = WIN_H;
	}
	y = (WIN_H - height) / 2;
	if (coll.dir & NORTH)
		fill_with_texture(&g_game.texture[NO], new_pos(x, y, 0),
			height, textures_index(coll.pos, offset, height, 1));
    ...
 ```   
 - Added shadow
    
<a href="https://ibb.co/vwW6qcL"><img src="https://i.ibb.co/HFyf4KG/3.png" alt="3" border="0"></a><br/>
 
 - Correct fish-eye effect
 - Correct jerky walls caused by conversion float to int

<a href="https://gifyu.com/image/SzuFG"><img img width="640" height="300" src="https://s10.gifyu.com/images/5589dafaba77a99b0.gif" alt="5589dafaba77a99b0.gif" border="0" /></a><br/>
    
 - Added texture on wall just to see how it fit
    
<a href="https://ibb.co/6wHQQ6S"><img src="https://i.ibb.co/qjN66b8/6.png" alt="6" border="0"></a><br/>
    
- Added real texture without offset so it only work when you see the complete wall. The wall didn't look good up close
    
<a href="https://ibb.co/pdfQDFp"><img src="https://i.ibb.co/7KnQcmF/7.png" alt="7" border="0"></a><br/>
    
 - Correct the offset so you can now zoom in on the wall and it still look good. To do so we used the _fill_with_texture_ function that calculate an appropriate step between the wall height and the texture image.
```C
void	fill_with_texture(t_img *text, t_pos pos, float height, t_pos index)
{
	t_img	*img;
	double	y_step;
	int		bytes;
	int		color;

	img = &g_game.game_img;
	y_step = ((float)text->height - (index.y * 2))
		/ (height + (img->height - height) / TILE_SIZE);
	bytes = (text->bpp / 8);
	color = 0;
	while (pos.y < height + (img->height - height) / 2)
	{
		color = color_get(*text, (int)index.x, (int)index.y);
		color = color_shift_int(color, BLACK, ((WIN_H - height) / WIN_H) / 2);
		if (pos.x >= 0 && pos.x < img->width)
			my_mlx_pixel_put(*img, pos.x, pos.y + g_game.player.pos.z, color);
		index.y += y_step;
		pos.y++;
	}
}
```
 - Added a gun sprite that animate when key is pressed.
 - At this stage we also added the parsing part where the program read a .cub file and determined if all requirement are met to load it properly.
    
<a href="https://gifyu.com/image/SzuF1"><img width="640" height="300" src="https://s10.gifyu.com/images/9c46c8d48067558f3.gif" alt="9c46c8d48067558f3.gif" border="0" /></a><br/>
 
 - Added a minimap in the top corner.
 - Since using the mlx transparency was'nt working very well, we create a function for custom transparency that shifted the present color using the pixel right under it.
 ```C
int	color_shift_int(int base, int shift, double force)
{
	t_rgb	rgb;
	t_rgb	base_rgb;
	t_rgb	shift_rgb;

	if (base == TRANS)
		return (base);
	base_rgb = color_int_to_rgb(base);
	shift_rgb = color_int_to_rgb(shift);
	rgb = color_shift_rgb(base_rgb, shift_rgb, force);
	return (color_rgb_to_int(rgb));
}
 ```
 - Added an animated enemy sprite that can be position in the .cub file.
 - Added doors that position themselves like the enemies but use a new character in the .cub map for their positions. They also can be interact with using a key pressed and the distance between the player and the door.
 - Added a script that calculate which sprite is the closest and draw them in last so they are not superposed.
 - Finally we added the mouse movement using mlx events.
    
<a href="https://gifyu.com/image/SzuFO"><img width="640" height="300" src="https://s10.gifyu.com/images/11e9a6cc7adb451779.gif" alt="11e9a6cc7adb451779.gif" border="0" /></a><br/>
    
**Thanks for reading!**

# Ressources

- <a href="http://users.atw.hu/wolf3d/">Original Wolfenstein 3D game</a> 
- <a href="https://lodev.org/cgtutor/raycasting.html">Raytracing tutorial</a>
- <a href="https://github.com/qst0/ft_libgfx">X11 Event number</a>
- <a href="https://harm-smits.github.io/42docs/libs/minilibx">MinilibX 42 Docs</a>
- <a href="https://www.calculat.org/fr/aire-perimetre/triangle-rectangle.html">Right Triangle calculator</a>
- <a href="https://www.youtube.com/watch?v=eOCQfxRQ2pY">Wolfenstein 3D's map renderer video</a>
- <a href="https://www.youtube.com/watch?v=vYgIKn7iDH8">Rendering raycasting video</a>
- <a href="https://www.youtube.com/watch?v=NbSee-XM7WA&t=1393s">Super Fast Ray Casting in Tiled Worlds using DDA video</a>
