/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:32:08 by sabras            #+#    #+#             */
/*   Updated: 2024/10/14 16:46:18 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotate_left(t_player *player, double rotate_speed)
{
	double	old_dir_x;

	old_dir_x = player->dir_x;
	player->dir_x = (old_dir_x * cos(-rotate_speed))
		- (player->dir_y * sin(-rotate_speed));
	player->dir_y = (old_dir_x * sin(-rotate_speed))
		+ (player->dir_y * cos(-rotate_speed));
	return (1);
}

int	rotate_right(t_player *player, double rotate_speed)
{
	double	old_dir_x;

	old_dir_x = player->dir_x;
	player->dir_x = (old_dir_x * cos(rotate_speed))
		- (player->dir_y * sin(rotate_speed));
	player->dir_y = (old_dir_x * sin(rotate_speed))
		+ (player->dir_y * cos(rotate_speed));
	return (1);
}