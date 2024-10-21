/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_design.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:49:19 by msimao            #+#    #+#             */
/*   Updated: 2024/10/21 01:49:32 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(char *file, t_data *data);
static void	save_wall(char *str, t_data *data, char **filename);
static void	save_rgb(char *str, t_data *data, int *rgb);
static int	display_info(char *str, t_data *data);

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
	free_split(data->map->tab_cp);
}

static void	check_file(char *file, t_data *data)
{
	char	*extension;
	int		fd;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".xpm"))
		error_gnl("the file extension must be '.xpm'", file, data);
	if (open(file, O_DIRECTORY) > 0)
		error_gnl("is a directory", file, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_gnl("cannot open file", file, data);
	close(fd);
}

static void	save_wall(char *str, t_data *data, char **filename)
{
	int		i;

	i = 0;
	if (*filename)
		error_gnl("unexpected line", str, data);
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] && !ft_isalpha(str[i++])) || (str[i] && !ft_isalpha(str[i++])))
		error_gnl("unexpected character", str, data);
	if (!str[i] || (str[i] && !ft_isspace(str[i])))
		error_gnl("unexpected character", str, data);
	while (str[i] && ft_isspace(str[i]))
		i++;
	*filename = ft_strdup(str + i);
	free(str);
	if (!*filename)
		throw_error(data, "cannot open file");
	check_file(*filename, data);
}

static void	save_rgb(char *str, t_data *data, int *rgb)
{
	int		i;

	i = 0;
	if (*rgb != 0)
		error_gnl("unexpected line", str, data);
	while (ft_isspace(str[i]))
		i++;
	i += 1;
	if (!str[i] || (str[i] && !ft_isspace(str[i])))
		error_gnl("unexpected character", str, data);
	while (str[i] && ft_isspace(str[i]))
		i++;
	*rgb = rgb_toi(str + i);
	if (*rgb < 0)
		error_gnl("invalid color", str, data);
	free(str);
}

static int	display_info(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == 'N' && str[i + 1] && str[i + 1] == 'O')
		return (save_wall(str, data, &data->map->wall_no), 1);
	else if (str[i] && str[i] == 'S' && str[i + 1] && str[i + 1] == 'O')
		return (save_wall(str, data, &data->map->wall_so), 1);
	else if (str[i] && str[i] == 'W' && str[i + 1] && str[i + 1] == 'E')
		return (save_wall(str, data, &data->map->wall_we), 1);
	else if (str[i] && str[i] == 'E' && str[i + 1] && str[i + 1] == 'A')
		return (save_wall(str, data, &data->map->wall_ea), 1);
	else if (str[i] && str[i] == 'F')
		return (save_rgb(str, data, &data->map->floor), 1);
	else if (str[i] && str[i] == 'C')
		return (save_rgb(str, data, &data->map->ceiling), 1);
	else if (ft_isprint(str[i]))
		error_gnl("unexpected character", str, data);
	return (free(str), 0);
}
