/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:19:25 by sabras            #+#    #+#             */
/*   Updated: 2024/10/21 16:23:38 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_door(t_player *player, char **map, int *door_x, int *door_y);
static int	is_valid_position(char **map, double pos_x, double pos_y);

void	toggle_nearest_door(t_data *data, char **map)
{
	int	x;
	int	y;

	if (!find_door(data->player, map, &x, &y))
		return ;
	if (map[y][x] == 'D')
		map[y][x] = 'O';
	else if (map[y][x] == 'O')
		map[y][x] = 'D';
}

void	display_door_message(t_data *data, char **map)
{
	int	screen_x;
	int	screen_y;
	int	door_x;
	int	door_y;

	screen_x = 40;
	screen_y = data->win_height - (data->win_height / 10);
	if (!find_door(data->player, map, &door_x, &door_y))
		return ;
	if (map[door_y][door_x] == 'D')
		mlx_string_put(data->mlx_ptr, data->win_ptr, screen_x, screen_y,
			0xFFFFFF, "Press [E] to open the door");
	else if (map[door_y][door_x] == 'O')
		mlx_string_put(data->mlx_ptr, data->win_ptr, screen_x, screen_y,
			0xFFFFFF, "Press [E] to close the door");
}

static int	find_door(t_player *player, char **map, int *door_x, int *door_y)
{
	double	rd;
	int		x;
	int		y;

	rd = 0.2;
	x = player->pos_x + player->dir_x;
	y = player->pos_y + player->dir_y;
	if (map[y][x] != 'D' && map[y][x] != 'O')
		return (0);
	if (!is_valid_position(map, player->pos_x + rd, player->pos_y + rd)
		|| !is_valid_position(map, player->pos_x + rd, player->pos_y - rd)
		|| !is_valid_position(map, player->pos_x - rd, player->pos_y + rd)
		|| !is_valid_position(map, player->pos_x - rd, player->pos_y - rd))
		return (0);
	*door_x = x;
	*door_y = y;
	return (1);
}

static int	is_valid_position(char **map, double pos_x, double pos_y)
{
	int	x;
	int	y;

	x = pos_x;
	y = pos_y;
	if (x < 0 || y < 0 || y >= tablen(map) || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == 'O')
		return (0);
	return (1);
}
