/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:10:36 by msimao            #+#    #+#             */
/*   Updated: 2024/10/22 13:25:54 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		calculate_minimap_size(t_data *data);
static void		put_pixel(t_data *data, int y, int x);
static int		get_color(t_data *data, double y, double x);

void	render_minimap(t_data *data)
{
	int		start_x;
	int		start_y;
	int		x;
	int		y;

	start_y = MINIMAP_MARGIN_HEIGHT;
	start_x = MINIMAP_MARGIN_WIDTH;
	data->minimap_size = calculate_minimap_size(data);
	y = start_y;
	while (y < data->minimap_size + start_y)
	{
		x = start_x;
		while (x < data->minimap_size + start_x)
			put_pixel(data, y, x++);
		y++;
	}
	render_arrow(data);
}

static int	calculate_minimap_size(t_data *data)
{
	int	minimap_size;
	int	width;
	int	height;

	width = data->win_width / 5;
	height = data->win_height / 5;
	if (width < height)
		minimap_size = width;
	else
		minimap_size = height;
	if (minimap_size % 2 == 0)
		minimap_size += 1;
	return (minimap_size);
}

static void	put_pixel(t_data *data, int y, int x)
{
	double	start_y;
	double	start_x;
	int		color;

	start_y = x - (MINIMAP_MARGIN_HEIGHT + (data->minimap_size / 2));
	start_x = y - (MINIMAP_MARGIN_WIDTH + (data->minimap_size / 2));
	color = get_color(data, start_y, start_x);
	put_pixel_on_img(&data->img_tab[RENDERING], y, x, color);
}

static int	get_color(t_data *data, double y, double x)
{
	int	map_y;
	int	map_x;

	map_y = (data->player->pos_y * MINIMAP_SQUARE_SIZE + y);
	map_x = (data->player->pos_x * MINIMAP_SQUARE_SIZE + x);
	map_y /= MINIMAP_SQUARE_SIZE;
	map_x /= MINIMAP_SQUARE_SIZE;
	if (map_y < 0 || map_x < 0 || (map_y >= tablen(data->map->tab))
		|| (map_x >= (int)ft_strlen(data->map->tab[map_y]))
		|| data->map->tab[map_y][map_x] == ' '
		|| data->map->tab[map_y][map_x] == '1')
		return (MINIMAP_COLOR_WALL);
	else if (data->map->tab[map_y][map_x] == '0')
		return (MINIMAP_COLOR_EMPTY);
	else if (data->map->tab[map_y][map_x] == 'D')
		return (MINIMAP_COLOR_DOOR_CLOSE);
	else if (data->map->tab[map_y][map_x] == 'O')
		return (MINIMAP_COLOR_DOOR_OPEN);
	return (0);
}
