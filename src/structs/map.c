/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:47:37 by sabras            #+#    #+#             */
/*   Updated: 2024/10/11 15:00:40 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*init_map(t_data *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		throw_error(data, "malloc failure");
	map->wall_no = NULL;
	map->wall_so = NULL;
	map->wall_ea = NULL;
	map->wall_we = NULL;
	map->ceiling = 0;
	map->floor = 0;
	map->fd = 0;
	map->start_count = 0;
	map->map = NULL;
	map->map_cp = NULL;
	return (map);
}

void	clear_map(t_map *map)
{
	free(map->wall_no);
	free(map->wall_so);
	free(map->wall_ea);
	free(map->wall_we);
	free_split(map->map);
	free(map);
}
