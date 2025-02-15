/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 09:45:54 by sabras            #+#    #+#             */
/*   Updated: 2024/10/22 18:58:46 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_img(t_data *data, t_img *img, char *filename);

void	create_images(t_data *data)
{
	create_img(data, &data->img_tab[WALL_NO], data->map->wall_no);
	create_img(data, &data->img_tab[WALL_SO], data->map->wall_so);
	create_img(data, &data->img_tab[WALL_EA], data->map->wall_ea);
	create_img(data, &data->img_tab[WALL_WE], data->map->wall_we);
	create_img(data, &data->img_tab[DOOR], IMG_DOOR);
	create_img(data, &data->img_tab[ARROW], IMG_ARROW);
	create_img(data, &data->img_tab[WEAPON], IMG_WEAPON);
	create_img(data, &data->img_tab[WEAPON_SHOOT], IMG_WEAPON_SHOOT_0);
	create_img(data, &data->img_tab[WEAPON_SHOOT + 1], IMG_WEAPON_SHOOT_1);
	create_img(data, &data->img_tab[WEAPON_RELOAD], IMG_WEAPON_RELOAD_0);
	create_img(data, &data->img_tab[WEAPON_RELOAD + 1], IMG_WEAPON_RELOAD_1);
	create_img(data, &data->img_tab[WEAPON_RELOAD + 2], IMG_WEAPON_RELOAD_2);
	create_img(data, &data->img_tab[WEAPON_RELOAD + 3], IMG_WEAPON_RELOAD_3);
	create_img(data, &data->img_tab[WEAPON_RELOAD + 4], IMG_WEAPON_RELOAD_4);
	create_img(data, &data->img_tab[BACKGROUND], NULL);
	create_img(data, &data->img_tab[RENDERING], NULL);
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->win_width)
	{
		y = 0;
		while (y < data->win_height)
		{
			if (y < data->win_height / 2)
				put_pixel_on_img(&data->img_tab[BACKGROUND], x, y,
					data->map->ceiling);
			else
				put_pixel_on_img(&data->img_tab[BACKGROUND], x, y,
					data->map->floor);
			y++;
		}
		x++;
	}
	data->background_size = (data->win_width * data->win_height)
		* (data->img_tab[BACKGROUND].bits_per_pixel / 8);
}

void	put_pixel_on_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	destroy_images(t_data *data, t_img *img_tab)
{
	int	i;

	i = 0;
	while (i < IMG_COUNT && img_tab[i].ptr)
		mlx_destroy_image(data->mlx_ptr, img_tab[i++].ptr);
}

static void	create_img(t_data *data, t_img *img, char *filename)
{
	if (filename)
		img->ptr = mlx_xpm_file_to_image(data->mlx_ptr, filename,
				&img->width, &img->height);
	else
		img->ptr = mlx_new_image(data->mlx_ptr,
				data->win_width, data->win_height);
	if (!img->ptr)
		throw_error(data, "Cannot create image");
	set_img_addr(data, img);
}
