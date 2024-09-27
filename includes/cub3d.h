/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:09:34 by sabras            #+#    #+#             */
/*   Updated: 2024/09/27 10:07:17 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include </home/sabras/sgoinfre/minilibx/mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define WIN_TITLE "42-Cub3D"

typedef struct s_data	t_data;
typedef struct s_map	t_map;

struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
};

struct s_map
{
	int	no;
	int	so;
	int	ea;
	int	we;
	int	c;
	int	f;
};

// --- Parsing ---
// map.c
void	check_map(char *file, t_data *data);
void	parse_design(int fd, t_map *map);
void	remove_nl(char *str);
void	error_gnl(char *err, char *str, t_map *map);
void	error_op(void);

// --- UI ---
// window.c
void	init_window(t_data *data);

// --- Structs ---
// data.c
t_data	init_data(void);
void	clear_data(t_data *data);

// map.c
t_map	*init_map(t_data *data);
void	clear_map(t_map *map);

// --- Utils ---
// error.c
void	error_file(char *str, t_map *map);
void	throw_error(t_data *data, char *err);

#endif
