/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:35:43 by sabras            #+#    #+#             */
/*   Updated: 2024/10/18 15:34:12 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move(t_player *player, char **map, double new_x, double new_y);

void	move_forward(t_player *player, char **map, double move_speed)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos_x + player->dir_x * move_speed;
	new_pos_y = player->pos_y + player->dir_y * move_speed;
	move(player, map, new_pos_x, new_pos_y);
}

void	move_backward(t_player *player, char **map, double move_speed)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos_x - player->dir_x * move_speed;
	new_pos_y = player->pos_y - player->dir_y * move_speed;
	move(player, map, new_pos_x, new_pos_y);
}

void	move_left(t_player *player, char **map, double move_speed)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos_x - player->plane_x * move_speed;
	new_pos_y = player->pos_y - player->plane_y * move_speed;
	move(player, map, new_pos_x, new_pos_y);
}

void	move_right(t_player *player, char **map, double move_speed)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos_x + player->plane_x * move_speed;
	new_pos_y = player->pos_y + player->plane_y * move_speed;
	move(player, map, new_pos_x, new_pos_y);
}

static void	move(t_player *player, char **map, double new_x, double new_y)
{
	if ((map[(int)(player->pos_y + 0.2)][(int)(new_x + 0.2)] != '1')
		&& (map[((int)(player->pos_y + 0.2))][(int)(new_x - 0.2)] != '1')
		&& (map[((int)(player->pos_y - 0.2))][(int)(new_x + 0.2)] != '1')
		&& (map[((int)(player->pos_y - 0.2))][(int)(new_x - 0.2)] != '1'))
		player->pos_x = new_x;
	if ((map[(int)(new_y + 0.2)][(int)(player->pos_x + 0.2)] != '1')
		&& (map[((int)(new_y - 0.2))][(int)(player->pos_x + 0.2)] != '1')
		&& (map[((int)(new_y + 0.2))][(int)(player->pos_x - 0.2)] != '1')
		&& (map[((int)(new_y - 0.2))][(int)(player->pos_x - 0.2)] != '1'))
		player->pos_y = new_y;
}
