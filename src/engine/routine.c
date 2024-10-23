/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:59 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 19:50:34 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		handle_moves(t_data *data, double elapsed_time);
static void		handle_shoot(t_data *data);

int	routine(t_data *data)
{
	double	current_time;

	current_time = get_current_time();
	handle_moves(data, current_time - data->last_tick);
	handle_shoot(data);
	if ((current_time - data->last_frame) > (1000.0 / FPS))
	{
		render_scene(data, current_time);
		data->last_frame = current_time;
	}
	display_door_message(data, data->map->tab);
	data->last_tick = current_time;
	return (0);
}

static void	handle_moves(t_data *data, double elapsed_time)
{
	double	move_speed;
	double	rotate_speed;

	move_speed = MOVE_SPEED * (elapsed_time / 1000.0);
	rotate_speed = ROTATE_SPEED * (elapsed_time / 1000.0);
	if (((data->keys->key_w && !data->keys->key_s)
			|| (!data->keys->key_w && data->keys->key_s))
		&& ((data->keys->key_a && !data->keys->key_d)
			|| (!data->keys->key_a && data->keys->key_d)))
		move_speed /= 1.5;
	if (data->keys->key_w)
		move_forward(data->player, data->map->tab, move_speed);
	if (data->keys->key_s)
		move_backward(data->player, data->map->tab, move_speed);
	if (data->keys->key_a)
		move_left(data->player, data->map->tab, move_speed);
	if (data->keys->key_d)
		move_right(data->player, data->map->tab, move_speed);
	if (data->keys->key_left)
		rotate_left(data->player, rotate_speed);
	if (data->keys->key_right)
		rotate_right(data->player, rotate_speed);
}

static void	handle_shoot(t_data *data)
{
	if (data->keys->button_left)
		shoot_with_weapon(data);
}

int	is_valid_move(char **map, double pos_x, double pos_y)
{
	int	x;
	int	y;

	x = pos_x;
	y = pos_y;
	if (x < 0 || y < 0 || y >= tablen(map) || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'D')
		return (0);
	return (1);
}
