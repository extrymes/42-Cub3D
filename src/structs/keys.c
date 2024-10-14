/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:51:36 by sabras            #+#    #+#             */
/*   Updated: 2024/10/10 14:08:28 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_keys	*init_keys(t_data *data)
{
	t_keys	*keys;

	keys = malloc(sizeof(t_keys));
	if (!keys)
		throw_error(data, "malloc failure");
	keys->key_w = 0;
	keys->key_s = 0;
	keys->key_a = 0;
	keys->key_d = 0;
	keys->key_left = 0;
	keys->key_right = 0;
	keys->key_esc = 0;
	return (keys);
}
