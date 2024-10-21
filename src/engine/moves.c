/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:35:43 by sabras            #+#    #+#             */
/*   Updated: 2024/10/21 16:23:20 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move(t_player *player, char **map, double new_x, double new_y);

void	move_forward(t_player *player, char **map, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * move_speed;
	new_y = player->pos_y + player->dir_y * move_speed;
	move(player, map, new_x, new_y);
}

void	move_backward(t_player *player, char **map, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * move_speed;
	new_y = player->pos_y - player->dir_y * move_speed;
	move(player, map, new_x, new_y);
}

void	move_left(t_player *player, char **map, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->plane_x * move_speed;
	new_y = player->pos_y - player->plane_y * move_speed;
	move(player, map, new_x, new_y);
}

void	move_right(t_player *player, char **map, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->plane_x * move_speed;
	new_y = player->pos_y + player->plane_y * move_speed;
	move(player, map, new_x, new_y);
}

static void	move(t_player *player, char **map, double new_x, double new_y)
{
	double	rd;

	rd = 0.2;
	if (is_valid_move(map, new_x + rd, player->pos_y + rd)
		&& is_valid_move(map, new_x + rd, player->pos_y - rd)
		&& is_valid_move(map, new_x - rd, player->pos_y + rd)
		&& is_valid_move(map, new_x - rd, player->pos_y - rd))
		player->pos_x = new_x;
	if (is_valid_move(map, player->pos_x + rd, new_y + rd)
		&& is_valid_move(map, player->pos_x - rd, new_y + rd)
		&& is_valid_move(map, player->pos_x + rd, new_y - rd)
		&& is_valid_move(map, player->pos_x - rd, new_y - rd))
		player->pos_y = new_y;
}
