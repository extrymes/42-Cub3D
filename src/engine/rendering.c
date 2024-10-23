/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:03:56 by sabras            #+#    #+#             */
/*   Updated: 2024/10/23 13:09:55 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_data *data, t_ray *ray, int col_height, int y);
static int	get_column(t_ray *ray, t_img *texture);

void	render_scene(t_data *data, double current_time)
{
	render_background(data);
	raycast_map(data);
	render_minimap(data);
	render_crosshair(data);
	render_weapon(data, get_weapon_img(data, current_time), current_time);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_tab[RENDERING].ptr, 0, 0);
	display_door_message(data, data->map->tab);
}

void	render_column(t_data *data, t_ray *ray, int x)
{
	int	col;
	int	col_height;
	int	col_start;
	int	col_end;
	int	y;

	col_height = (int)(data->win_height / ray->per_wall_dist);
	col_start = -col_height / 2 + data->win_height / 2;
	if (col_start < 0)
		col_start = 0;
	col_end = col_height / 2 + data->win_height / 2;
	if (col_end >= data->win_height)
		col_end = data->win_height - 1;
	col = x;
	while (x < col + VERTICAL_SLICING)
	{
		y = col_start;
		while (y < col_end)
		{
			put_pixel_on_img(&data->img_tab[RENDERING], x, y,
				get_color(data, ray, col_height, y));
			y++;
		}
		x++;
	}
}

void	render_background(t_data *data)
{
	ft_memcpy(data->img_tab[RENDERING].addr, data->img_tab[BACKGROUND].addr,
		data->background_size);
}

static int	get_color(t_data *data, t_ray *ray, int col_height, int y)
{
	t_img	texture;
	int		tex_x;
	int		tex_y;
	int		color;
	char	*pixel;

	if (ray->wall_hit == '1')
		texture = data->img_tab[ray->wall_face];
	else if (ray->wall_hit == 'D')
		texture = data->img_tab[DOOR];
	tex_x = get_column(ray, &texture);
	tex_y = (int)(((y - (-col_height / 2 + data->win_height / 2))
				* texture.height) / col_height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture.height)
		tex_y = texture.height - 1;
	pixel = texture.addr + (tex_y * texture.line_length
			+ (tex_x * (texture.bits_per_pixel / 8)));
	color = *(unsigned int *)pixel;
	return (color);
}

static int	get_column(t_ray *ray, t_img *texture)
{
	int		tex_x;
	double	wall_hit;

	if (ray->wall_side == 0)
		wall_hit = ray->pos_y + ray->per_wall_dist * ray->dir_y;
	else
		wall_hit = ray->pos_x + ray->per_wall_dist * ray->dir_x;
	wall_hit -= floor(wall_hit);
	tex_x = (int)(wall_hit * (double)(texture->width));
	if ((ray->wall_side == 0 && ray->dir_x > 0)
		|| (ray->wall_side == 1 && ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}
