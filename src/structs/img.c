/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:19:24 by sabras            #+#    #+#             */
/*   Updated: 2024/10/21 16:59:45 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	init_img(void)
{
	t_img	img;

	img.ptr = NULL;
	img.addr = NULL;
	img.width = 0;
	img.height = 0;
	img.bits_per_pixel = 0;
	img.line_length = 0;
	img.endian = 0;
	return (img);
}

t_img	*init_img_tab(t_data *data)
{
	t_img	*img_tab;
	int		i;

	img_tab = malloc(IMG_COUNT * sizeof(t_img));
	if (!img_tab)
		throw_error(data, "Malloc failure");
	i = 0;
	while (i < IMG_COUNT)
		img_tab[i++] = init_img();
	return (img_tab);
}

void	set_img_addr(t_data *data, t_img *img)
{
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		throw_error(data, "Cannot get image addr");
}
