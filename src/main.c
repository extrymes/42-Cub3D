/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:09:13 by sabras            #+#    #+#             */
/*   Updated: 2024/10/21 00:56:27 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd(RED "Usage:\n\t./cub3d <map.cub>\n" RESET, 2), 1);
	data = init_data();
	check_map(av[1], &data);
	create_images(&data);
	draw_background(&data);
	render_scene(&data);
	SET_FONT(data.mlx_ptr, data.win_ptr, "10x20");
	track_mouse(&data);
	handle_events(&data);
	return (clear_data(&data), 0);
}
