/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:17:34 by sabras            #+#    #+#             */
/*   Updated: 2024/09/24 10:38:07 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_newline(char *buffer, char *newline);
static char	*ft_strjoin2(char *s1, char *s2);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			readed;

	line = ft_strdup(buffer);
	while (1)
	{
		newline = ft_strchr(line, '\n');
		if (newline)
			break ;
		readed = read(fd, buffer, BUFFER_SIZE);
		if (!readed || readed < 0)
			break ;
		buffer[readed] = '\0';
		line = ft_strjoin2(line, buffer);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	if (newline)
		handle_newline(buffer, newline);
	else
		buffer[0] = '\0';
	return (line);
}

static void	handle_newline(char *buffer, char *newline)
{
	ft_strcpy(buffer, newline + 1);
	*(newline + 1) = '\0';
}

static char	*ft_strjoin2(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcpy(joined + ft_strlen(s1), s2);
	free(s1);
	return (joined);
}
