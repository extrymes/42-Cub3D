/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:49:05 by sabras            #+#    #+#             */
/*   Updated: 2024/10/24 11:31:51 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_destroy(t_data *data)
{
	clear_data(data);
	return (exit(EXIT_SUCCESS), 0);
}

void	throw_error(t_data *data, char *err)
{
	if (data->map->fd > 0)
		close(data->map->fd);
	ft_putstr_fd(RED "Error\n", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n" RESET, 2);
	clear_data(data);
	exit(EXIT_FAILURE);
}
