/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_design.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:49:19 by msimao            #+#    #+#             */
/*   Updated: 2024/10/12 11:53:31 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(char *file, t_data *data)
{
	char	*extension;
	int		fd;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".xpm"))
		error_gnl("The file extension must be '.xpm'", file, data);
	if (open(file, O_DIRECTORY) > 0)
		error_gnl("Is a directory", file, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_gnl("Cannot open file", file, data);
	close(fd);
}

static char	*save_wall(char *str, t_data *data, char *filename)
{
	int		i;
	char	*file;

	i = 0;
	if (filename)
		error_gnl("Unexpected line", str, data);
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] && !ft_isalpha(str[i++])) || (str[i] && !ft_isalpha(str[i++])))
		error_gnl("Unexpected character", str, data);
	if (!str[i] || (str[i] && !ft_isspace(str[i])))
		error_gnl("Unexpected character", str, data);
	while (str[i] && ft_isspace(str[i]))
		i++;
	file = ft_strdup(str + i);
	free(str);
	if (!file)
		error_gnl("Malloc fail", file, data);
	check_file(file, data);
	return (file);
}

static int	save_rgb(char *str, t_data *data, int rgb)
{
	int		i;
	int		res;

	i = 0;
	if (rgb != 0)
		error_gnl("Unexpected line", str, data);
	while (ft_isspace(str[i]))
		i++;
	i += 1;
	if (!str[i] || (str[i] && !ft_isspace(str[i])))
		error_gnl("Unexpected character", str, data);
	while (str[i] && ft_isspace(str[i]))
		i++;
	res = rgb_toi(str + i);
	if (res < 0)
		error_gnl("Invalid color", str, data);
	free(str);
	return (res);
}

static int	display_info(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == 'N'  && str[i + 1] && str[i + 1] == 'O')
		return (data->map->wall_no = save_wall(str, data, data->map->wall_no), 1);
	else if (str[i] && str[i] == 'S'  && str[i + 1] && str[i + 1] == 'O')
		return (data->map->wall_so = save_wall(str, data, data->map->wall_so), 1);
	else if (str[i] && str[i] == 'W'  && str[i + 1] && str[i + 1] == 'E')
		return (data->map->wall_we = save_wall(str, data, data->map->wall_we), 1);
	else if (str[i] && str[i] == 'E'  && str[i + 1] && str[i + 1] == 'A')
		return (data->map->wall_ea = save_wall(str, data, data->map->wall_ea), 1);
	else if (str[i] && str[i] == 'F')
		return (data->map->floor = save_rgb(str, data, data->map->floor), 1);
	else if (str[i] && str[i] == 'C')
		return (data->map->ceiling = save_rgb(str, data, data->map->ceiling), 1);
	else if (ft_isprint(str[i]))
		error_gnl("Unexpected character", str, data);
	return (free(str), 0);
}

void	parse_design(t_data *data)
{
	char	*str;
	int		nbr_design;

	nbr_design = 0;
	while (1)
	{
		str = get_next_line(data->map->fd);
		if (str == NULL)
			break ;
		remove_nl(str);
		if (nbr_design < 6)
			nbr_design += display_info(str, data);
		else
			save_map(str, data->map);
	}
	close(data->map->fd);
	parse_map(data);
	free_split(data->map->map_cp);
}
