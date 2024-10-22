/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:15:40 by sabras            #+#    #+#             */
/*   Updated: 2024/10/22 21:15:34 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_crosshair(t_data *data)
{
	int	x;
	int	y;
	int	i;

	if (data->weapon_status == WEAPON_STATUS_RELOADING)
		return ;
	x = data->win_width / 2;
	y = data->win_height / 2;
	i = -1;
	while (++i < 10)
		put_pixel_on_img(&data->img_tab[RENDERING], x + 5 + i, y, 0xFFFFFF);
	i = -1;
	while (++i < 10)
		put_pixel_on_img(&data->img_tab[RENDERING], x - 5 - i, y, 0xFFFFFF);
	i = -1;
	while (++i < 10)
		put_pixel_on_img(&data->img_tab[RENDERING], x, y + 5 + i, 0xFFFFFF);
	i = -1;
	while (++i < 10)
		put_pixel_on_img(&data->img_tab[RENDERING], x, y - 5 - i, 0xFFFFFF);
}
