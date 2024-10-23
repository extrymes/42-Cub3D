/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:04:27 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 13:49:58 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse_move(int x, int y, t_data *data)
{
	int				win_center_x;
	int				delta_x;
	double			current_time;
	double			rotate_speed;
	static double	last_move = 0.0;

	(void)y;
	if (!data->mouse_tracked)
		return (0);
	win_center_x = data->win_width / 2;
	delta_x = x - win_center_x;
	current_time = get_current_time();
	rotate_speed = MOUSE_SPEED * ((current_time - data->last_tick) / 1000.0);
	if (delta_x < 0)
		rotate_left(data->player, abs(delta_x) * rotate_speed);
	else if (delta_x > 0)
		rotate_right(data->player, delta_x * rotate_speed);
	if ((current_time - last_move) > 5.0)
	{
		MOUSE_MOVE(data->mlx_ptr, data->win_ptr, win_center_x,
			data->win_height / 2);
		last_move = current_time;
	}
	return (0);
}

void	track_mouse(t_data *data)
{
	int	win_center_x;
	int	win_center_y;

	win_center_x = data->win_width / 2;
	win_center_y = data->win_height / 2;
	MOUSE_HIDE(data->mlx_ptr, data->win_ptr);
	MOUSE_MOVE(data->mlx_ptr, data->win_ptr, win_center_x, win_center_y);
	data->mouse_tracked = 1;
}

void	untrack_mouse(t_data *data)
{
	MOUSE_SHOW(data->mlx_ptr, data->win_ptr);
	data->mouse_tracked = 0;
}

void	toggle_mouse_tracking(t_data *data)
{
	if (!data->mouse_tracked)
		track_mouse(data);
	else
		untrack_mouse(data);
}
