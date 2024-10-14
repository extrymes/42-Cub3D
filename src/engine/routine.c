/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:59 by sabras            #+#    #+#             */
/*   Updated: 2024/10/14 17:53:23 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_moves(t_data *data, double current_time);

int	routine(t_data *data)
{
	double	current_time;

	current_time = get_current_time();
	if (handle_moves(data, current_time))
		render_scene(data);
	if (data->keys->key_esc)
		handle_destroy(data);
	data->last_tick = current_time;
	return (0);
}

static int	handle_moves(t_data *data, double current_time)
{
	double	move_speed;
	double	rotate_speed;
	int		moved;

	move_speed = MOVE_SPEED * (current_time - data->last_tick);
	rotate_speed = ROTATE_SPEED * (current_time - data->last_tick);
	moved = 0;
	if (data->keys->key_w)
		moved = move_forward(data->player, move_speed);
	if (data->keys->key_s)
		moved = move_backward(data->player, move_speed);
	if (data->keys->key_a)
		moved = move_left(data->player, move_speed);
	if (data->keys->key_d)
		moved = move_right(data->player, move_speed);
	if (data->keys->key_left)
		moved = rotate_left(data->player, rotate_speed);
	if (data->keys->key_right)
		moved = rotate_right(data->player, rotate_speed);
	return (moved);
}
