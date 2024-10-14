/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:05 by sabras            #+#    #+#             */
/*   Updated: 2024/10/14 13:07:21 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	init_data(void)
{
	t_data	data;
	int		i;

	data.mlx_ptr = mlx_init();
	data.win_ptr = NULL;
	data.map = NULL;
	data.img_tab = NULL;
	data.player = NULL;
	data.background_size = 0;
	if (!data.mlx_ptr)
		throw_error(&data, "mlx: init failure");
	GET_SCREEN_SIZE(data.mlx_ptr, &data.win_width, &data.win_height);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win_width, data.win_height,
			WIN_TITLE);
	if (!data.win_ptr)
		throw_error(&data, "mlx: cannot create window");
	data.img_tab = malloc(IMG_COUNT * sizeof(t_img));
	if (!data.img_tab)
		throw_error(&data, "malloc failure");
	i = 0;
	while (i < IMG_COUNT)
		data.img_tab[i++] = init_img();
	data.player = init_player(&data);
	data.keys = init_keys(&data);
	return (data);
}

void	clear_data(t_data *data)
{
	clear_map(data->map);
	if (data->img_tab)
	{
		destroy_images(data, data->img_tab);
		free(data->img_tab);
	}
	if (data->player)
		free(data->player);
	if (data->keys)
		free(data->keys);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		DESTROY_DISPLAY(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}
