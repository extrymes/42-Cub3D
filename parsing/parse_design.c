/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_design.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:49:19 by msimao            #+#    #+#             */
/*   Updated: 2024/10/09 11:21:26 by msimao           ###   ########.fr       */
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
	if (open(file, __O_DIRECTORY) > 0)
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
	return (data->map->done++, file);
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
	return (data->map->done++, res);
}

static void	display_info(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == 'N'  && str[i + 1] && str[i + 1] == 'O')
		data->map->no = save_wall(str, data, data->map->no);
	else if (str[i] && str[i] == 'S'  && str[i + 1] && str[i + 1] == 'O')
		data->map->so = save_wall(str, data, data->map->so);
	else if (str[i] && str[i] == 'W'  && str[i + 1] && str[i + 1] == 'E')
		data->map->we = save_wall(str, data, data->map->we);
	else if (str[i] && str[i] == 'E'  && str[i + 1] && str[i + 1] == 'A')
		data->map->ea = save_wall(str, data, data->map->ea);
	else if (str[i] && str[i] == 'F')
		data->map->f = save_rgb(str, data, data->map->f);
	else if (str[i] && str[i] == 'C')
		data->map->c = save_rgb(str, data, data->map->c);
	else if (ft_isprint(str[i]))
		error_gnl("Unexpected character", str, data);
	else
		free(str);
}

void	parse_design(int fd, t_data *data)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		remove_nl(str);
		if (data->map->done < 6)
			display_info(str, data);
		else
			save_map(str, data->map);
	}
	close(fd);
	parse_map(data);
	free_split(data->map->map_cp);
}
