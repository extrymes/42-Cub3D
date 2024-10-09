/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:47:37 by sabras            #+#    #+#             */
/*   Updated: 2024/10/09 11:20:52 by msimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*init_map(t_data *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		throw_error(data, "malloc failure");
	map->done = 0;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->c = 0;
	map->f = 0;
	map->fd = 0;
	map->nb = 0;
	map->map = NULL;
	map->map_cp = NULL;
	return (map);
}

void	clear_map(t_map *map)
{
	free(map->ea);
	free(map->no);
	free(map->so);
	free(map->we);
	free_split(map->map);
	free(map);
}
