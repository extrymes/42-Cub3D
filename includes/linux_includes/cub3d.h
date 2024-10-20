/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:09:34 by sabras            #+#    #+#             */
/*   Updated: 2024/10/20 18:34:50 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# define WIN_TITLE "42-Cub3D"
# define IMG_COUNT 7
# define WALL_NO 0
# define WALL_SO 1
# define WALL_EA 2
# define WALL_WE 3
# define ARROW 4
# define BACKGROUND 5
# define RENDERING 6
# define FOV 90.0
# define FPS 60.0
# define MINIMAP_MARGIN_HEIGHT 40
# define MINIMAP_MARGIN_WIDTH 40
# define MINIMAP_SQUARE_SIZE 20
# define VERTICAL_SLICING 2
# define MOVE_SPEED 3.0
# define ROTATE_SPEED 2.5
# define MOUSE_SENSITIVITY 0.02
# define KEY_ESC XK_Escape
# define KEY_CTRL XK_Control_L
# define KEY_W XK_w
# define KEY_S XK_s
# define KEY_A XK_a
# define KEY_D XK_d
# define KEY_LEFT XK_Left
# define KEY_RIGHT XK_Right
# define KEYPRESS KeyPress
# define KEYPRESSMASK KeyPressMask
# define KEYRELEASE KeyRelease
# define KEYRELEASEMASK KeyReleaseMask
# define MOTIONNOTIFY MotionNotify
# define POINTERMOTIONMASK PointerMotionMask
# define DESTROYNOTIFY DestroyNotify
# define STRUCTURENOTIFYMASK StructureNotifyMask
# define MOUSE_HIDE(mlx_ptr, win_ptr) mlx_mouse_hide(mlx_ptr, win_ptr)
# define MOUSE_SHOW(mlx_ptr, win_ptr) mlx_mouse_show(mlx_ptr, win_ptr)
# define MOUSE_MOVE(mlx_ptr, win_ptr, x, y) mlx_mouse_move(mlx_ptr, win_ptr, x, y);
# define GET_SCREEN_SIZE(mlx_ptr, win_width, win_height) mlx_get_screen_size(mlx_ptr, win_width, win_height)
# define DESTROY_DISPLAY(mlx_ptr) mlx_destroy_display(mlx_ptr)

// -- Structures --
typedef struct s_data	t_data;
typedef struct s_map	t_map;
typedef struct s_img	t_img;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_coord	t_coord;
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
	int		start_count;
	char	**tab;
	char	**tab_cp;
	char	player;
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
};

// --- Parsing ---
// map.c
void		check_map(char *file, t_data *data);
void		parse_design(t_data *data);
void		save_map(char *str, t_map *map);
void		parse_map(t_data *data);

int			rgb_toi(char *str);
int			len_tab(char **tab);
void		remove_nl(char *str);
void		error_gnl(char *err, char *str, t_data *data);
void		error_map(char *err, t_data *data);
int			count_digit(char *str);
void		free_split(char **tab);
void		copy_map(t_data *data);

// --- Engine ---
// raycasting.c
void		raycasting(t_data *data);

// rendering.c
void		render_scene(t_data *data);
void		render_column(t_data *data, t_ray *ray, int x);
void		render_background(t_data *data);

// events.c
void		handle_events(t_data *data);

// routine.c
int			routine(t_data *data);

// minimap.c
void		render_minimap(t_data *data);

// moves.c
void		move_forward(t_player *player, char **map, double move_speed);
void		move_backward(t_player *player, char **map, double move_speed);
void		move_left(t_player *player, char **map, double move_speed);
void		move_right(t_player *player, char **map, double move_speed);

// rotates.c
void		rotate_left(t_player *player, double rotate_speed);
void		rotate_right(t_player *player, double rotate_speed);

// mouse.c
void		track_mouse(t_data *data);
void		untrack_mouse(t_data *data);
void		toggle_mouse_tracking(t_data *data);

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
// images.c
void		create_images(t_data *data);
void		draw_background(t_data *data);
void		put_pixel_on_img(t_img *img, int x, int y, int color);
void		destroy_images(t_data *data, t_img *img_tab);

// time.c
double		get_current_time(void);

// error.c
void		throw_error(t_data *data, char *err);

#endif
