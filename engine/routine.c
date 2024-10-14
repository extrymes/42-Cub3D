/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:59 by sabras            #+#    #+#             */
/*   Updated: 2024/10/14 12:39:54 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_moves(t_data *data);
static int	check_move_keys(t_keys	*keys);

int	routine(t_data *data)
{
	if (check_move_keys(data->keys))
	{
		handle_moves(data);
		raycasting(data);
	}
	else
		data->player->last_move = get_time_in_sec();
	if (data->keys->key_esc)
		handle_destroy(data);
	return (0);
}

static void	handle_moves(t_data *data)
{
	double	current_time;
	double	move_speed;
	double	rotate_speed;

	current_time = get_time_in_sec();
	move_speed = MOVE_SPEED * (current_time - data->player->last_move);
	rotate_speed = ROTATE_SPEED * (current_time - data->player->last_move);
	data->player->last_move = current_time;
	if (data->keys->key_w)
		move_forward(data->player, move_speed);
	if (data->keys->key_s)
		move_backward(data->player, move_speed);
	if (data->keys->key_a)
		move_left(data->player, move_speed);
	if (data->keys->key_d)
		move_right(data->player, move_speed);
	if (data->keys->key_left)
		rotate_left(data->player, rotate_speed);
	if (data->keys->key_right)
		rotate_right(data->player, rotate_speed);
}

static int	check_move_keys(t_keys	*keys)
{
	if (keys->key_w || keys->key_s || keys->key_a || keys->key_d
		|| keys->key_left || keys->key_right)
		return (1);
	return (0);
}
