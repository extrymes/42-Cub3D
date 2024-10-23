/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:23:14 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 14:43:23 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		throw_error(data, "Cannot init mlx");
	GET_SCREEN_SIZE(data->mlx_ptr, &data->win_width, &data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width,
			data->win_height, WIN_TITLE);
	if (!data->win_ptr)
		throw_error(data, "Cannot create window");
}
