/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:51:09 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 19:47:17 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_weapon_move(double current_time);

void	render_weapon(t_data *data, t_img *weapon, double current_time)
{
	int	x;
	int	y;
	int	j;
	int	i;
	int	color;

	(void)current_time;
	x = data->win_width - weapon->width;
	y = data->win_height - (weapon->height - get_weapon_move(current_time));
	j = 0;
	i = 0;
	while (i < weapon->height)
	{
		j = 0;
		while (j < weapon->width)
		{
			color = *(int *)(weapon->addr + (i * weapon->line_length
						+ j * (weapon->bits_per_pixel / 8)));
			if (color != 0)
				put_pixel_on_img(&data->img_tab[RENDERING],
					x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static int	get_weapon_move(double current_time)
{
	static int		dir = 0;
	static int		move = 0;
	static double	last_move = 0.0;

	if (current_time - last_move < 50.0)
		return (move);
	if (move == 0 || move == 15)
		dir = !dir;
	if (dir)
		move++;
	else
		move--;
	last_move = current_time;
	return (move);
}

t_img	*get_weapon_img(t_data *data, double current_time)
{
	const int		weapon_shoot[] = {7, 8, 7, -1};
	const int		weapon_reload[] = {11, 9, 10, 9, 11, 12, 13, -1};
	static double	last_anime = 0.0;
	static int		i = -1;
	int				weapon_id;

	if (data->weapon_status != WEAPON_STATUS_NORMAL
		&& (i == -1 || current_time - last_anime > 150.0))
	{
		i++;
		last_anime = current_time;
	}
	weapon_id = WEAPON;
	if (data->weapon_status == WEAPON_STATUS_SHOOTING)
		weapon_id = weapon_shoot[i];
	else if (data->weapon_status == WEAPON_STATUS_RELOADING)
		weapon_id = weapon_reload[i];
	if (weapon_id == -1)
		return (i = -1, data->weapon_status = WEAPON_STATUS_NORMAL,
			&data->img_tab[WEAPON]);
	return (&data->img_tab[weapon_id]);
}

void	shoot_with_weapon(t_data *data)
{
	if (data->weapon_status != WEAPON_STATUS_NORMAL)
		return ;
	if (data->weapon_capacity == 0)
		return (reload_weapon(data));
	data->weapon_status = WEAPON_STATUS_SHOOTING;
	data->weapon_capacity--;
}

void	reload_weapon(t_data *data)
{
	if (data->weapon_status != WEAPON_STATUS_NORMAL)
		return ;
	data->weapon_status = WEAPON_STATUS_RELOADING;
	data->weapon_capacity = WEAPON_CAPACITY;
}
