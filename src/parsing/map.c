/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:32:56 by msimao            #+#    #+#             */
/*   Updated: 2024/10/24 11:29:14 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(char *file, t_data *data);

void	check_map(char *file, t_data *data)
{
	data->map = init_map(data);
	check_file(file, data);
	data->map->fd = open(file, O_RDONLY);
	if (data->map->fd < 0)
		throw_error(data, "Cannot open file");
	parse_design(data);
}

static void	check_file(char *file, t_data *data)
{
	char	*extension;
	int		fd;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".cub"))
		throw_error(data, "The file extension must be '.cub'");
	fd = open(file, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		throw_error(data, "Is a directory");
	}
}
