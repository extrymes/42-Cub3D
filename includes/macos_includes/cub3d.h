/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:49:44 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 21:13:38 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# define WIN_TITLE "42-Cub3D"
# define IMG_COUNT 16
# define WALL_NO 0
# define WALL_SO 1
# define WALL_EA 2
# define WALL_WE 3
# define DOOR 4
# define ARROW 5
# define WEAPON 6
# define WEAPON_SHOOT 7
# define WEAPON_RELOAD 9
# define BACKGROUND 14
# define RENDERING 15
# define IMG_DOOR "textures/door.xpm"
# define IMG_ARROW "textures/arrow.xpm"
# define IMG_WEAPON "textures/weapon.xpm"
# define IMG_WEAPON_SHOOT_0 "textures/weapon_shoot0.xpm"
# define IMG_WEAPON_SHOOT_1 "textures/weapon_shoot1.xpm"
# define IMG_WEAPON_RELOAD_0 "textures/weapon_reload0.xpm"
# define IMG_WEAPON_RELOAD_1 "textures/weapon_reload1.xpm"
# define IMG_WEAPON_RELOAD_2 "textures/weapon_reload2.xpm"
# define IMG_WEAPON_RELOAD_3 "textures/weapon_reload3.xpm"
# define IMG_WEAPON_RELOAD_4 "textures/weapon_reload4.xpm"
# define MINIMAP_MARGIN_HEIGHT 40
# define MINIMAP_MARGIN_WIDTH 40
# define MINIMAP_SQUARE_SIZE 20
# define MINIMAP_COLOR_EMPTY 0x0
# define MINIMAP_COLOR_WALL 0x464646
# define MINIMAP_COLOR_DOOR_OPEN 0x41B54F
# define MINIMAP_COLOR_DOOR_CLOSE 0xB54141
# define FOV 90.0
# define FPS 120.0
# define VERTICAL_SLICING 2
# define MOVE_SPEED 3.0
# define ROTATE_SPEED 2.5
# define MOUSE_SPEED 0.1
# define WEAPON_CAPACITY 5
# define WEAPON_STATUS_NORMAL 0
# define WEAPON_STATUS_SHOOTING 1
# define WEAPON_STATUS_RELOADING 2
# define KEY_ESC 53
# define KEY_CTRL 256
# define KEY_E 14
# define KEY_R 15
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define BUTTON_LEFT 1
# define KEYPRESS 2
# define KEYPRESSMASK 1L<<0
# define KEYRELEASE 3
# define KEYRELEASEMASK 1L<<1
# define BUTTONPRESS 4
# define BUTTONPRESSMASK 1L<<2
# define BUTTONRELEASE 5
# define BUTTONRELEASEMASK 1L<<3
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK 1L<<6
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK 0
# define MOUSE_HIDE(mlx_ptr, win_ptr) mlx_mouse_hide()
# define MOUSE_SHOW(mlx_ptr, win_ptr) mlx_mouse_show()
# define MOUSE_MOVE(mlx_ptr, win_ptr, x, y) mlx_mouse_move(win_ptr, x, y);
# define SET_FONT(mlx_ptr, win_ptr, font)
# define GET_SCREEN_SIZE(mlx_ptr, win_width, win_height) *win_width = 1600; *win_height = 1000
# define DESTROY_DISPLAY(mlx_ptr)

// -- Structures --
typedef struct s_data	t_data;
typedef struct s_map	t_map;
typedef struct s_img	t_img;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_keys	t_keys;

struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
	double		last_frame;
	double		last_tick;
	int			mouse_tracked;
	int			weapon_status;
	int			weapon_capacity;
	int			minimap_size;
	size_t		background_size;
	t_map		*map;
	t_img		*img_tab;
	t_player	*player;
	t_keys		*keys;
};

struct s_map
{
	int		fd;
	char	*wall_no;
	char	*wall_so;
	char	*wall_ea;
	char	*wall_we;
	int		ceiling;
	int		floor;
	int		starting_count;
	char	**tab;
	char	**tab_cp;
};

struct s_img
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
};

struct s_ray
{
	double	pos_x;
	double	pos_y;
	int		rough_x;
	int		rough_y;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		wall_side;
	int		wall_face;
	char	wall_hit;
	double	per_wall_dist;
};

struct s_keys
{
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_left;
	int	key_right;
	int	button_left;
};

// --- Engine ---
// raycasting.c
void		raycast_map(t_data *data);

// rendering.c
void		render_scene(t_data *data, double current_time);
void		render_column(t_data *data, t_ray *ray, int x);
void		render_background(t_data *data);

// events.c
void		handle_events(t_data *data);

// routine.c
int			routine(t_data *data);
int			is_valid_move(char **map, double pos_x, double pos_y);

// minimap.c
void		render_minimap(t_data *data);

// minimap_arrow.c
void		render_arrow(t_data *data);

// door.c
void		toggle_nearest_door(t_data *data, char **map);
void		display_door_message(t_data *data, char **map);

// moves.c
void		move_forward(t_player *player, char **map, double move_speed);
void		move_backward(t_player *player, char **map, double move_speed);
void		move_left(t_player *player, char **map, double move_speed);
void		move_right(t_player *player, char **map, double move_speed);

// rotates.c
void		rotate_left(t_player *player, double rotate_speed);
void		rotate_right(t_player *player, double rotate_speed);

// mouse.c
int			handle_mouse_move(int x, int y, t_data *data);
void		track_mouse(t_data *data);
void		untrack_mouse(t_data *data);
void		toggle_mouse_tracking(t_data *data);

// weapon.c
void		render_weapon(t_data *data, t_img *weapon, double current_time);
t_img		*get_weapon_img(t_data *data, double current_time);
void		shoot_with_weapon(t_data *data);
void		reload_weapon(t_data *data);

// crosshair.c
void		render_crosshair(t_data *data);

// --- Parsing ---
// map.c
void		check_map(char *file, t_data *data);

// parse_map.c
void		parse_map(t_data *data);

// parse_design.c
void		parse_design(t_data *data);

// parse_utils.c
void		error_gnl(char *err, char *str, t_data *data);
void		error_map(char *err, t_data *data);
void		remove_nl(char *str);
void		free_split(char **tab);
int			count_digit(char *str);

// parse_utils2.c
int			rgb_toi(char *str);
void		save_map(char *str, t_map *map);
void		copy_map(t_data *data);
int			tablen(char **tab);

// --- Structs ---
// data.c
t_data		init_data(void);
void		clear_data(t_data *data);

// map.c
t_map		*init_map(t_data *data);
void		clear_map(t_map *map);

// img.c
t_img		init_img(void);
t_img		*init_img_tab(t_data *data);
void		set_img_addr(t_data *data, t_img *img);

// player.c
t_player	*init_player(t_data *data);

// ray.c
t_ray		*init_ray(t_data *data, double plane_x, double plane_y, int x);

// keys.c
t_keys		*init_keys(t_data *data);

// --- Utils ---
// window.c
void		create_window(t_data *data);

// images.c
void		create_images(t_data *data);
void		draw_background(t_data *data);
void		put_pixel_on_img(t_img *img, int x, int y, int color);
void		destroy_images(t_data *data, t_img *img_tab);

// time.c
double		get_current_time(void);

// exit.c
int			handle_destroy(t_data *data);
void		throw_error(t_data *data, char *err);

#endif
