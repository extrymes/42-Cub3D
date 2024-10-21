/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:59 by sabras            #+#    #+#             */
/*   Updated: 2024/10/21 15:29:09 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_moves(t_data *data, double elapsed_time);

int	routine(t_data *data)
{
	double	current_time;

	current_time = get_current_time();
	handle_moves(data, current_time - data->last_tick);
	if ((current_time - data->last_frame) > (1000.0 / FPS))
	{
		render_scene(data);
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
