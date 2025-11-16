/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:13:19 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/16 19:56:36 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <ft_printf.h>
# include <libft.h>
# include <get_next_line.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <mlx_extended.h>

# define WIDTH       1600
# define HEIGHT      1000
# define M_PI        3.14159265358979323846

typedef struct s_vec3
{
    float x;
    float y;
    float z;
}                t_vec3;

typedef struct s_mat4
{
    float m[4][4];
}                 t_mat4;

typedef struct s_window_render
{
    mlx_context mlx;
    void *win;
    void *img;
    mlx_color pixels[HEIGHT * WIDTH];
} t_window_render;

typedef struct s_map_pars
{
	int	x_max;
	int	y_max;
	char	**all_line;
	int		*map;
	unsigned long	*color_map;
}				t_map_pars;

typedef struct s_map
{
	int	x_max;
	int	y_max;
	int	**z_matrix;
}				t_map;

#endif
