/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:40:36 by msimao            #+#    #+#             */
/*   Updated: 2024/10/18 03:21:23 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static void	flood_fill(t_map *map, int x, int y, t_data *data)
{
	if ((int)ft_strlen(map->tab_cp[y]) <= 1)
		error_map("Invalid map", data);
	if (y < 0 || x < 0 || map->tab_cp[y][x] == ' '
		|| y >= len_tab(map->tab_cp) || x >= (int)ft_strlen(map->tab_cp[y]))
		error_map("Invalid map", data);
	if (map->tab_cp[y][x] == '0' || map->tab_cp[y][x] == map->player
		|| map->tab_cp[y][x] == 'D')
	{
		map->tab_cp[y][x] = '1';
		flood_fill(map, x + 1, y, data);
		flood_fill(map, x - 1, y, data);
		flood_fill(map, x, y + 1, data);
		flood_fill(map, x, y - 1, data);
	}
	else if (map->tab_cp[y][x] != '1')
		error_map("Invalid char", data);
}

static void	set_player(t_data *data, char c, int y, int x)
{
	data->player->pos_y = y + 0.5;
	data->player->pos_x = x + 0.5;
	data->map->player = data->map->tab[y][x];
	if (c == 'N')
		data->player->dir_y = -1.0;
	else if (c == 'S')
		data->player->dir_y = 1.0;
	else if (c == 'E')
		data->player->dir_x = 1.0;
	else if (c == 'W')
		data->player->dir_x = -1.0;
	data->map->start_count++;
}

void	parse_map(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->map->tab[++y])
	{
		x = -1;
		while (data->map->tab[y][++x])
		{
			if (data->map->tab[y][x] == 'N' || data->map->tab[y][x] == 'S'
				|| data->map->tab[y][x] == 'E' || data->map->tab[y][x] == 'W')
				set_player(data, data->map->tab[y][x], y, x);
			else if (data->map->tab[y][x] != '1' && data->map->tab[y][x] != ' '
				&& data->map->tab[y][x] != '0' && data->map->tab[y][x] != 'D')
				throw_error(data, "invalid char");
		}
	}
	if (data->map->start_count != 1)
		throw_error(data, "number player invalid");
	copy_map(data);
	flood_fill(data->map, data->player->pos_x, data->player->pos_y, data);
}
