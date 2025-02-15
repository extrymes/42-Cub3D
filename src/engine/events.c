/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:43:22 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 20:39:58 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_keypress(int keycode, t_data *data);
static int	handle_keyrelease(int keycode, t_data *data);
static int	handle_buttonpress(int button, int x, int y, t_data *data);
static int	handle_buttonrelease(int button, int x, int y, t_data *data);

void	handle_events(t_data *data)
{
	mlx_hook(data->win_ptr, KEYPRESS, KEYPRESSMASK,
		handle_keypress, data);
	mlx_hook(data->win_ptr, KEYRELEASE, KEYRELEASEMASK,
		handle_keyrelease, data);
	mlx_hook(data->win_ptr, BUTTONPRESS, BUTTONPRESSMASK,
		handle_buttonpress, data);
	mlx_hook(data->win_ptr, BUTTONRELEASE, BUTTONRELEASEMASK,
		handle_buttonrelease, data);
	mlx_hook(data->win_ptr, MOTIONNOTIFY, POINTERMOTIONMASK,
		handle_mouse_move, data);
	mlx_hook(data->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
		handle_destroy, data);
	mlx_loop_hook(data->mlx_ptr, routine, data);
	mlx_loop(data->mlx_ptr);
}

static int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys->key_w = 1;
	else if (keycode == KEY_S)
		data->keys->key_s = 1;
	else if (keycode == KEY_A)
		data->keys->key_a = 1;
	else if (keycode == KEY_D)
		data->keys->key_d = 1;
	else if (keycode == KEY_LEFT)
		data->keys->key_left = 1;
	else if (keycode == KEY_RIGHT)
		data->keys->key_right = 1;
	else if (keycode == KEY_R)
		reload_weapon(data);
	else if (keycode == KEY_E)
		toggle_nearest_door(data, data->map->tab);
	else if (keycode == KEY_CTRL)
		toggle_mouse_tracking(data);
	else if (keycode == KEY_ESC)
		handle_destroy(data);
	return (0);
}

static int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys->key_w = 0;
	else if (keycode == KEY_S)
		data->keys->key_s = 0;
	else if (keycode == KEY_A)
		data->keys->key_a = 0;
	else if (keycode == KEY_D)
		data->keys->key_d = 0;
	else if (keycode == KEY_LEFT)
		data->keys->key_left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys->key_right = 0;
	return (0);
}

static int	handle_buttonpress(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == BUTTON_LEFT)
		data->keys->button_left = 1;
	return (0);
}

static int	handle_buttonrelease(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == BUTTON_LEFT)
		data->keys->button_left = 0;
	return (0);
}
