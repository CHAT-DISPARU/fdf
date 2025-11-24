/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:13:19 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 17:02:34 by gajanvie         ###   ########.fr       */
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

# define WIDTH       1500
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

typedef struct s_screen_coords
{
    float	tx;
    float	ty;
	float	x;
	float	y;
	float	z;
	float	norm_x;
	float	norm_y;
	float	theta;
	float	phi;
}                 t_screen_coords;

typedef struct	s_mat4_iso
{
	float	ax;
    float	ay;
    float	cx;
    float	sx;
    float	cy;
    float	sy;
}				t_mat4_iso;

typedef struct	s_all_mat4
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	proj;
	t_mat4	mvp;
	t_mat4	mv;
	t_mat4	rotate;
	t_mat4	rotate_x;
	t_mat4	rotate_y;
	t_mat4	rotate_z;
}				t_all_mat4;

typedef struct	s_lerp_color
{
    unsigned char	r1;
    unsigned char	g1;
    unsigned char	b1;
    unsigned char	r2;
    unsigned char	g2;
    unsigned char	b2;
    unsigned char	r;
    unsigned char	g;
    unsigned char	b;
	
}				t_lerp_color;

typedef struct	s_linear_interpolation
{
	float			t;
	int				max_step;
	int				step;
}				t_linear_interpolation;

typedef struct s_line_algo
{
    unsigned int	dx;
    unsigned int	dy;
    int 			sx;
	int				sy;
	int				err;
	int				e2;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	unsigned int				color;
	unsigned int				color2;
}                 t_line_algo;

typedef struct s_window_render
{
    mlx_context mlx;
    void *win;
    void *img;
    mlx_color pixels[HEIGHT * WIDTH];
	float	zoom;
	int		*map;
	unsigned int	*color_map;
	unsigned int	*color_map2;
	unsigned int	*color_map3;
	int	x_max;
	int	y_max;
	float	y_axe;
	float	x_axe;
	t_mat4	mvp;
	int	color_bool;
	int		*map_screen;
	int		color_back;
	int		key_table[512];
	int		old_key_table[512];
	int		line_show;
	float		deph;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	int		view_i;
	int		sphere;
	float	sphere_radius;
	int		size_points;
	int		speed;
	int		help;
} t_window_render;

typedef struct s_map_pars
{
	char	**all_line;
}				t_map_pars;

typedef struct s_multiple_index
{
	int		i;
	int		k;
	int		j;
	int		n;
}				t_multiple_index;

typedef struct s_map
{
	int	x_max;
	int	y_max;
	int	**z_matrix;
}				t_map;

void	get_screen_pos(t_vec3 p, int *sx, int *sy, t_window_render *data);
t_mat4	mat4_multiply(t_mat4 *a, t_mat4 *b);
void mat4_initial(t_mat4 *mat);
t_mat4	render_isometric(t_window_render *data);
void mat4_rotate_y(t_mat4 *m, float angle);
void mat4_rotate_x(t_mat4 *m, float angle);
void mat4_rotate_z(t_mat4 *m, float angle);
void create_ortho_projection(t_mat4 *proj, t_window_render *data);
void create_view(t_mat4 *view);
t_mat4	render_parallel(t_window_render *data);
void	draw_line(t_window_render *data);
void	algo_line(t_window_render *data, int idx, int idx2);
void	draw_every_point(t_window_render *data);
void key_hook(int key, void* param);
void key_up(int key, void* param);
void key_down(int key, void* param);
void window_hook(int event, void* param);
void mouse_hook(int button, int x, int y, t_window_render *data);
unsigned int	rand_color(void);
void	fill_str(char **tab, char *new, char ***result);
int	ft_tabstrlen(char **c);
char	**ft_tabstrdup(char **src);
char	**ft_realloc_tab(char **tab, char *new);
int	map_valid(char	**all_line);
int	len_valid(t_map_pars *map_pars, t_window_render *data);
void cleanup_map(t_window_render *data);
int	parse_map(char *file, t_map_pars *map_pars, t_window_render *data);
void key_zoom(int button, void* param);
void	set_data(t_window_render *data);
unsigned int	find_color(int z);
void	clean_map_mlx(t_window_render *data);
unsigned int    lerp_color(unsigned int c1, unsigned int c2, float t);
void	create_window(t_window_render *data, mlx_window_create_info	*info);
void	create_menue(t_window_render *data);

#endif
