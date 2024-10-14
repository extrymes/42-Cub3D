/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:35:43 by sabras            #+#    #+#             */
/*   Updated: 2024/10/14 16:45:54 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_forward(t_player *player, double move_speed)
{
	player->pos_x += player->dir_x * move_speed;
	player->pos_y += player->dir_y * move_speed;
	return (1);
}

int	move_backward(t_player *player, double move_speed)
{
	player->pos_x -= player->dir_x * move_speed;
	player->pos_y -= player->dir_y * move_speed;
	return (1);
}

int	move_left(t_player *player, double move_speed)
{
	player->pos_x -= player->plane_x * move_speed;
	player->pos_y -= player->plane_y * move_speed;
	return (1);
}

int	move_right(t_player *player, double move_speed)
{
	player->pos_x += player->plane_x * move_speed;
	player->pos_y += player->plane_y * move_speed;
	return (1);
}
