/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:44:16 by msimao            #+#    #+#             */
/*   Updated: 2024/10/04 15:50:19 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_gnl(char *err, char *str, t_data *data)
{
	free(str);
	close(data->map->fd);
	throw_error(data, err);
}

void	error_map(char *err, t_data *data)
{
	free_split(data->map->map_cp);
	throw_error(data, err);
}

void	remove_nl(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str || len == 0)
		return ;
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	count_digit(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = ft_atoi(str);
	if (nbr > 255)
		return (-1);
	while (ft_isdigit(str[i]))
		i++;
	if (i > 3 || i <= 0)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (nbr);
}
