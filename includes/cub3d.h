/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:44:58 by sfournie          #+#    #+#             */
/*   Updated: 2024/12/03 23:58:07 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include	<stdarg.h>
# include	<stdio.h>
# include	<limits.h>
# include	<stddef.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<math.h>
# include	<complex.h>
# include	<fcntl.h>
# include	<mlx.h>
# include	"cub3d_struct.h"
# include	"../libft/libft.h"

# define FALSE		0
# define TRUE		1

# define WIN_W 		800
# define WIN_H		600
# define FPS		30.0
# define MLX_CD		10
# define MAP_PATH	"./maps/complex.cub"

/* Key for linux */

# define ESC 			65307
# define SPACE_KEY 		32
# define A_KEY			97
# define D_KEY			100
# define E_KEY			101
# define M_KEY			109
# define R_KEY	 		114
# define S_KEY			115
# define W_KEY			119
# define SHIFT_KEY		65505
# define RIGHT_KEY		65363
# define LEFT_KEY		65361  
# define DOWN_KEY		65362 
# define UP_KEY			65364 


/* Key for mac */
// # define ESC 			53
// # define SPACE_KEY 		49
// # define A_KEY			0
// # define D_KEY			2
// # define E_KEY			14
// # define M_KEY			46
// # define R_KEY	 		15
// # define S_KEY			1
// # define W_KEY			13
// # define SHIFT_KEY		257
// # define RIGHT_KEY		124
// # define LEFT_KEY		123
// # define UP_KEY			126
// # define DOWN_KEY		125

/* Game parameter */
# define MAP_MAX_SIZE	1000
# define SPEED			8
# define TURN_SPEED		8
# define VIEW_ANGLE		60
# define VIEW_DIST		1000
# define TILE_SIZE		50.0
# define TEXTURES_SIZE	32.0

/* Sprites */
# define SPRITE_AMNT	4

/* Colors */
# define TRANS			0x980088
# define WHITE			0xffffff
# define BLACK			0x000000
# define RED			0xFF0000
# define GRAY			0xAAAAAA
# define FLOOR_C		0x303030
# define CEILING_C		0x909090
# define BLUE			0x0000ff
# define YELLOW			0xf0de18

/* Map objects */
# define M_FLOOR		'0'
# define M_WALL			'1'
# define M_EMPTY		' '
# define M_PLYR_N		'N'
# define M_PLYR_S		'S'
# define M_PLYR_E		'E'
# define M_PLYR_W		'W'

/* Parse errors */
# define ERR_FILE		1
# define ERR_MAPC		2
# define ERR_WALL		3
# define ERR_SPACE		4
# define ERR_PLAYER		5
# define ERR_ARGC		6
# define ERR_TEXTURE	7
# define ERR_ID			8
# define ERR_MISS		9
# define ERR_COLOR		10
# define ERR_MAP_LAST	11

extern t_game	g_game;

/* Generic structure creator */
t_pos	new_pos(double x, double y, double z);
t_size	new_size(double x, double y, double z);
t_coll	new_collider(t_pos pos, int type, int dir);

/* MLX */
t_mlx	*get_mlx(void);

/* Image */
void	my_mlx_new_image(void *mlx, t_img *img, int width, int height);

/* Game management */
void	init_game(t_game *game);
void	init_textures(t_game *game);
void	exit_game(int exit_code);

/* Map management */
t_map	new_map(void);
t_img	create_background(double width, double height);
void	fill_map(char **rows, t_map *map_ptr, int width, int height);
int		get_map_index(int win_x, int win_y);
int		get_map_index_y(int win_y);
int		get_map_index_x(int win_x);

/* Parsing */
int		parse_map_is_enclosed(t_map map);
int		parse_valid_map_line(char *line, int *len);
int		parse_valid_map(t_map *map);
int		parse_valid_map_c(char c);
int		parse_map(char **line, t_map *map_ptr, int fd);
int		parse_cub(char *path);
int		parse_is_player(char c);
int		parse_error(int code);
int		parse_error_bonus(int code);
int		parse_wall(t_map map, int x, int y);
int		parse_floor(t_map map, int x, int y, int compare);
int		parse_f_c(char *colors, char id);
int		parse_map_pos(t_map map, int x, int y, int *player_found);
int		parse_identifier(char *line);

/* Image and draw */
void	my_mlx_pixel_put(t_img img, int x, int y, int color);
void	mlx_clear_img(t_img img);
void	drawMap3D(t_mlx *mlx, t_map map);
void	draw_background(t_img img);

/* Color */
int		color_valid_rgb(t_rgb rgb);
int		color_get(t_img img, int x, int y);
t_rgb	new_rgb(int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
t_rgb	color_int_to_rgb(int color);
int		color_rgb_to_int(t_rgb rgb);
t_rgb	color_shift_rgb(t_rgb base, t_rgb shift, double force);
int		color_shift_int(int base, int shift, double force);
void	fill_with_texture(t_img *text, t_pos pos, float height, t_pos index);
t_pos	textures_index(t_pos pos, float offset, float height, int side);

/* Inputs */
int		key_press(int keyww);
int		key_release(int key);
int		quit_handler(void);

/* Player */
t_plyr	get_plyr(void);
void	player_set_pos(int x, int y, int z);
int		player_get_facing(t_plyr player);

/* Position and movement */
void	move_player(void);
t_pos	move_pos(t_pos pos, double rot, double dist, int dir);
int		rotate_player(t_plyr *player, double rot);
double	rotate(double base_rot, double rot);
int		change_player_pos(t_plyr *player, double vel, int dir);

/* Raycasting */
int		raycast_draw_all(t_pos pos, double rot, double view);

/* Collision and intersection */
int		check_collision(int x, int y, int size, int map);
t_coll	check_intersections(double x, double y, double rot);
int		check_inter_y(t_pos inter);
int		check_inter_x(t_pos inter);
t_coll	check_dir(t_pos inter_y, t_pos inter_x, int side, double rot);

/* Math */
double	deg_to_rad(double angle);
double	rad_to_deg(double rad);
double	get_draw_distance(t_pos pos, double rot, t_pos pixel, double angle);
int		angle_is_between(double angle, double min, double max);
double	math_pytha(double x, double y);

#endif