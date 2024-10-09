/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:37:04 by msimao            #+#    #+#             */
/*   Updated: 2024/10/04 15:50:19 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_toi(char *str)
{
	int		nb1;
	int		nb2;
	int		nb3;
	char	**rgb;

	rgb = ft_split(str, ',');
	nb1 = count_digit(rgb[0]);
	if (nb1 < 0)
		return (free_split(rgb), -1);
	nb2 = count_digit(rgb[1]);
	if (nb2 < 0)
		return (free_split(rgb), -1);
	nb3 = count_digit(rgb[2]);
	if (nb3 < 0)
		return (free_split(rgb), -1);
	if (rgb[3])
		return (free_split(rgb), -1);
	free_split(rgb);
	return ((nb1 << 16) + (nb2 << 8) + nb3);
}

static char	**ft_realloc_map(t_map *map, int size)
{
	char	**new_map;
	int		i;

	new_map = malloc((size + 2) * sizeof(char *));
	if (!new_map)
		return (free_split(map->map), NULL);
	i = 0;
	while (i < size)
	{
		new_map[i] = ft_strdup(map->map[i]);
		if (!new_map[i])
			return (free_split(map->map), free_split(new_map), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (free_split(map->map), new_map);
}

void	save_map(char *str, t_map *map)
{
	int	i;

	i = len_tab(map->map);
	map->map = ft_realloc_map(map, i);
	if (!map->map)
		return (free(str));
	map->map[i] = ft_strdup(str);
	free(str);
	if (!map->map[i])
		return (free_split(map->map));
	map->map[i + 1] = 0;
}

void	copy_map(t_data *data)
{
	int	i;

	i = 0;
	data->map->map_cp = malloc(sizeof(char *) * (len_tab(data->map->map) + 1));
	if (data->map->map_cp == NULL)
		throw_error(data, "malloc failure");
	while (i < len_tab(data->map->map))
	{
		data->map->map_cp[i] = ft_strdup(data->map->map[i]);
		if (data->map->map_cp[i] == NULL)
			throw_error(data, "malloc failure");
		i++;
	}
	data->map->map_cp[i] = 0;
}
