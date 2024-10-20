/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:04:27 by sabras            #+#    #+#             */
/*   Updated: 2024/10/20 18:37:52 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	track_mouse(t_data *data)
{
	MOUSE_HIDE(data->mlx_ptr, data->win_ptr);
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
