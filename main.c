/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:09:13 by sabras            #+#    #+#             */
/*   Updated: 2024/10/09 12:10:03 by sabras           ###   ########.fr       */
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
	background(&data);
	raycasting(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_tab[RENDER].ptr, 0, 0);
	handle_events(&data);
	return (clear_data(&data), 0);
}
