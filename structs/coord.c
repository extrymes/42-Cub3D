/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:38:19 by msimao            #+#    #+#             */
/*   Updated: 2024/10/09 12:31:24 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*init_ray(t_data *data)
{
	t_ray	*coord;

	coord = malloc(sizeof(t_ray));
	if (!coord)
		throw_error(data, "malloc failure");
	coord->pos_x = 0;
	coord->pos_y = 0;
	coord->dir_x = 0;
	coord->dir_y = 0;
	coord->total_dist = 0;
	coord->face = 0;
	coord->side = 0;
	return (coord);
}
