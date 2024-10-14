/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:23:22 by sabras            #+#    #+#             */
/*   Updated: 2024/10/14 16:28:36 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	*cast_ray(t_data *data, double plane_x, double plane_y, int x);
static void		hit_wall(t_data *data, t_ray *ray);
static int		get_wall_face(t_ray *ray);

void	raycasting(t_data *data)
{
	t_ray	*ray;
	double	fov_plane_scale;
	int		x;

	fov_plane_scale = tanf((FOV * (M_PI / 180.0)) / 2.0);
	data->player->plane_x = -data->player->dir_y * fov_plane_scale;
	data->player->plane_y = data->player->dir_x * fov_plane_scale;
	x = 0;
	while (x < data->win_width)
	{
		ray = cast_ray(data, data->player->plane_x, data->player->plane_y, x);
		render_column(data, ray, x);
		x += VERTICAL_SLICING;
		free(ray);
	}
}

static t_ray	*cast_ray(t_data *data, double plane_x, double plane_y, int x)
{
	t_ray	*ray;

	ray = init_ray(data, plane_x, plane_y, x);
	hit_wall(data, ray);
	ray->wall_face = get_wall_face(ray);
	if (ray->wall_side == 0)
		ray->per_wall_dist = (ray->rough_x - data->player->pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->per_wall_dist = (ray->rough_y - data->player->pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	return (ray);
}

static void	hit_wall(t_data *data, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->rough_x += ray->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->rough_y += ray->step_y;
			ray->wall_side = 1;
		}
		if (ray->rough_y < 0 || ray->rough_x < 0
			|| (ray->rough_y >= len_tab(data->map->map))
			|| (ray->rough_x >= (int)ft_strlen(data->map->map[ray->rough_y])))
			return (free(ray), throw_error(data, "ray is out of map"));
		if (data->map->map[ray->rough_y][ray->rough_x] == '1')
			break ;
	}
}

static int	get_wall_face(t_ray *ray)
{
	if (ray->wall_side == 0)
	{
		if (ray->dir_x > 0)
			return (WALL_WE);
		return (WALL_EA);
	}
	else
	{
		if (ray->dir_y > 0)
			return (WALL_NO);
		return (WALL_SO);
	}
}