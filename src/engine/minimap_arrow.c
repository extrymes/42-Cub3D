/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:52:46 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 10:15:05 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	create_img(t_data *data, int height, int width);
static void		rotate_image(t_img *src, t_img *dest, double angle);
static void		pixel_arrow(t_data *data, t_img *arrow, int i, int j);

void	render_arrow(t_data *data)
{
	int		i;
	int		j;
	t_img	rotated_arrow;
	double	angle;

	i = -1;
	rotated_arrow = create_img(data, 30, 30);
	angle = atan2(data->player->dir_y, data->player->dir_x) \
	- (2 * M_PI / 3) - 0.30;
	rotate_image(&data->img_tab[ARROW], &rotated_arrow, -angle);
	while (++i < rotated_arrow.height)
	{
		j = -1;
		while (++j < rotated_arrow.width)
			pixel_arrow(data, &rotated_arrow, i, j);
	}
	mlx_destroy_image(data->mlx_ptr, rotated_arrow.ptr);
}

static t_img	create_img(t_data *data, int height, int width)
{
	t_img	img;

	img.ptr = mlx_new_image(data->mlx_ptr,
			width, height);
	if (!img.ptr)
		throw_error(data, "Cannot create image");
	img.height = height;
	img.width = width;
	set_img_addr(data, &img);
	return (img);
}

static void	rotate_image(t_img *src, t_img *dest, double angle)
{
	int	new_x;
	int	new_y;
	int	j;
	int	i;
	int	color;

	i = -1;
	while (++i < src->height)
	{
		j = -1;
		while (++j < src->width)
		{
			new_x = (int)(cos(angle) * (j - src->width / 2) - sin(angle) * (\
				i - src->height / 2) + src->width / 2) + (dest->width / 4);
			new_y = (int)(sin(angle) * (j - src->width / 2) + cos(angle) * (\
				i - src->height / 2) + src->height / 2) + (dest->height / 4);
			color = *(int *)(src->addr + (i * src->line_length + j * (
							src->bits_per_pixel / 8)));
			if (new_x >= 0 && new_x < dest->width && new_y >= 0
				&& new_y < dest->height)
				*(int *)(dest->addr + (new_y * dest->line_length + new_x * (\
					dest->bits_per_pixel / 8))) = color;
		}
	}
}

static void	pixel_arrow(t_data *data, t_img *arrow, int i, int j)
{
	int	color;
	int	color1;
	int	color2;
	int	middle;

	middle = (data->minimap_size / 2);
	color = *(unsigned int *)(arrow->addr + (i * arrow->line_length + j * (\
		arrow->bits_per_pixel / 8)));
	if (color != 0)
		put_pixel_on_img(&data->img_tab[RENDERING],
			MINIMAP_MARGIN_HEIGHT + middle + i - (arrow->height / 2),
			MINIMAP_MARGIN_WIDTH + middle + j - (arrow->width / 2), 16777028);
	if (j > 0 && j < arrow->width - 1)
	{
		color1 = *(unsigned int *)(arrow->addr + (i * arrow->line_length \
			+ (j + 1) * (arrow->bits_per_pixel / 8)));
		color2 = *(unsigned int *)(arrow->addr + (i * arrow->line_length \
			+ (j - 1) * (arrow->bits_per_pixel / 8)));
		if (color1 != color && color2 != color)
		{
			put_pixel_on_img(&data->img_tab[RENDERING], \
			MINIMAP_MARGIN_HEIGHT + middle + i - (arrow->height / 2), \
			MINIMAP_MARGIN_WIDTH + middle + j - (arrow->width / 2), 16777028);
		}
	}
}
