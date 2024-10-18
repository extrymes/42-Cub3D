/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:37:04 by msimao            #+#    #+#             */
/*   Updated: 2024/10/18 03:21:23 by sabras           ###   ########.fr       */
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
		return (free_split(map->tab), NULL);
	i = 0;
	while (i < size)
	{
		new_map[i] = ft_strdup(map->tab[i]);
		if (!new_map[i])
			return (free_split(map->tab), free_split(new_map), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (free_split(map->tab), new_map);
}

void	save_map(char *str, t_map *map)
{
	int	i;

	i = len_tab(map->tab);
	map->tab = ft_realloc_map(map, i);
	if (!map->tab)
		return (free(str));
	map->tab[i] = ft_strdup(str);
	free(str);
	if (!map->tab[i])
		return (free_split(map->tab));
	map->tab[i + 1] = 0;
}

void	copy_map(t_data *data)
{
	int	i;

	i = 0;
	data->map->tab_cp = malloc(sizeof(char *) * (len_tab(data->map->tab) + 1));
	if (data->map->tab_cp == NULL)
		throw_error(data, "malloc failure");
	while (i < len_tab(data->map->tab))
	{
		data->map->tab_cp[i] = ft_strdup(data->map->tab[i]);
		if (data->map->tab_cp[i] == NULL)
			throw_error(data, "malloc failure");
		i++;
	}
	data->map->tab_cp[i] = 0;
}
