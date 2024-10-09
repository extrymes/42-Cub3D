/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:32:56 by msimao            #+#    #+#             */
/*   Updated: 2024/10/09 11:21:13 by msimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(char *file, t_data *data)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".cub"))
		throw_error(data, "the file extension must be '.cub'");
	if (open(file, __O_DIRECTORY) > 0)
		throw_error(data, "is a directory");
}

void	check_map(char *file, t_data *data)
{
	data->map = init_map(data);
	check_file(file, data);
	data->map->fd = open(file, O_RDONLY);
	if (data->map->fd < 0)
		throw_error(data, "cannot open file");
	parse_design(data->map->fd, data);
}
