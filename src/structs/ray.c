/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:38:19 by msimao            #+#    #+#             */
/*   Updated: 2024/10/14 18:10:38 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_step(t_ray *ray);
static void	calculate_side_dist(t_data *data, t_ray *ray);

t_ray	*init_ray(t_data *data, double plane_x, double plane_y, int x)
{
	t_ray	*ray;
	double	fov_ray_x;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		throw_error(data, "malloc failure");
	fov_ray_x = 2 * x / (double)data->win_width - 1;
	ray->pos_x = data->player->pos_x;
	ray->pos_y = data->player->pos_y;
	ray->rough_x = (int)data->player->pos_x;
	ray->rough_y = (int)data->player->pos_y;
	ray->dir_x = data->player->dir_x + plane_x * fov_ray_x;
	ray->dir_y = data->player->dir_y + plane_y * fov_ray_x;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	calculate_step(ray);
	calculate_side_dist(data, ray);
	ray->wall_side = 0;
	ray->wall_face = 0;
	ray->per_wall_dist = 0.0;
	return (ray);
}

static void	calculate_step(t_ray *ray)
{
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

static void	calculate_side_dist(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
		ray->side_dist_x = (data->player->pos_x - ray->rough_x)
			* ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->rough_x + 1.0 - data->player->pos_x)
			* ray->delta_dist_x;
	if (ray->dir_y < 0)
		ray->side_dist_y = (data->player->pos_y - ray->rough_y)
			* ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->rough_y + 1.0 - data->player->pos_y)
			* ray->delta_dist_y;
}
