/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:47:21 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/17 16:35:05 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>


void	fill_str(char **tab, char *new, char ***result)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		(*result)[j] = ft_strdup(tab[j]);
		j++;
	}
	(*result)[j++] = ft_strdup(new);
	(*result)[j] = NULL;
}


int	ft_tabstrlen(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	**ft_tabstrdup(char **src)
{
	char	**cpy_src;
	int		i;

	i = 0;
	while (src[i])
		i ++;
	cpy_src = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	if (cpy_src == NULL)
		return (NULL);
	while (src[i])
	{
		cpy_src[i] = ft_strdup(src[i]);
		i ++;
	}
	cpy_src[i] = NULL;
	return (cpy_src);
}

char	**ft_realloc_tab(char **tab, char *new)
{
	char	**result;
	int		i;

	if (!tab && !new)
		return (NULL);
	if (!tab)
	{
		result = malloc(sizeof(char *) * 2);
		result[0] = ft_strdup(new);
		result[1] = NULL;
		return (result);
	}
	i = ft_tabstrlen(tab);
	result = (char **)malloc(sizeof(char *) * (i + 2));
	if (!result)
		return (NULL);
	fill_str(tab, new, &result);
	if (tab)
		free_all(tab);
	//free(new);
	return (result);
}

void	mess_error(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

int	map_valid(char	**all_line)
{
	char	**line_split;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	while (all_line[i])
	{
		line_split = ft_split(all_line[i]);
		if (!line_split)
		{
			free_all(all_line);
			mess_error("malloc parsing:", EXIT_FAILURE);
		}
		k = 0;
		while (line_split[k])
		{
			j = 0;
			if (line_split[k][j] == '-')
				j++;
			while (line_split[k][j] >= '0' && line_split[k][j] <= '9')
				j++;
			if (line_split[k][j])
			{
				free_all(line_split);
				return (1);
			}
			k++;
		}
		free_all(line_split);
		i++;	
	}
	return (0);
}

int	len_valid (t_map_pars *map_pars, t_window_render *caca)
{
	char	**line_split;
	int		len;
	int		i;

	i = 0;
	line_split = ft_split(map_pars->all_line[i]);
	if (!line_split)
		mess_error("malloc parsing:", EXIT_FAILURE);
	len = ft_tabstrlen(line_split);
	free_all(line_split);
	i = 1;
	while (map_pars->all_line[i])
	{
		line_split = ft_split(map_pars->all_line[i]);
		if (!line_split)
			mess_error("malloc parsing:", EXIT_FAILURE);
		if (ft_tabstrlen(line_split) != len)
		{
			free_all(line_split);
			return (0);
		}
		free_all(line_split);
		i++;
	}
	caca->y_max = i;
	return (len);
}

void cleanup_map(t_window_render *caca)
{
    free(caca->map);
    free(caca->color_map);
    caca->map = NULL;
    caca->color_map = NULL;
}

void	convert_int(t_map_pars *map_pars, t_window_render *caca)
{	
	char	**line_split;
	int		i;
	int		k;
	int		j;
	int		n;
	char	*coma;
	char	*color_str;
	
	i = 0;
	j = 0;
	n = 0;
	caca->map = malloc (sizeof(int) * caca->y_max * caca->x_max * 3);
	caca->color_map = malloc (sizeof(long) * caca->y_max * caca->x_max);
	if (!caca->map || !caca->color_map)
	{
		if (!caca->color_map)
			free(caca->map);
        mess_error("malloc map", 1);
	}
	while (map_pars->all_line[i])
	{
		k = 0;
		line_split = ft_split(map_pars->all_line[i]);
		if (!line_split)
		{
			free_all(map_pars->all_line);
			cleanup_map(caca);
			mess_error("malloc parsing:", EXIT_FAILURE);
		}
		while (line_split[k])
		{
			coma = ft_strchr(line_split[k], ',');
			if (coma)
			{
				*coma = '\0';
				color_str = coma + 1;
				if (color_str[0] == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
                    color_str += 2;
				if (*color_str == '\0')
					caca->color_map[n] = 0xFFFFFFUL;
				else
					caca->color_map[n] = ft_atol_base(color_str, "0123456789abcdef");
			}
			else
				caca->color_map[n] = 0xFFFFFFUL;
			n++;
			caca->map[j] = k;
			caca->map[j + 1] = i;
			caca->map[j + 2] = ft_atoi(line_split[k]);
			j += 3;
			k++;
		}
		free_all(line_split);
		i++;	
	}
}

void	parse_map(char *file, t_map_pars *map_pars, t_window_render *caca)
{
	int	fd;
	char *line;

	map_pars->all_line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		mess_error("open map", 1);
	line = get_next_line(fd);
	while (line)
	{
		map_pars->all_line = ft_realloc_tab(map_pars->all_line, line);
		free(line);
		line = get_next_line(fd);
	}
	caca->x_max = len_valid(map_pars, caca);
	if (caca->x_max > 0)
		convert_int(map_pars, caca);
	else 
		caca->map = NULL;
	free_all(map_pars->all_line);
}

void	free_all_int_tabs(t_window_render *caca)
{
	free(caca->map);
	free(caca->color_map);
}

void mat4_initial(t_mat4 *mat)
{
    int	i;
    int	j;

    i = 0;
    while (i < 4)
	{
        j = 0;
        while (j < 4)
		{
            if (i == j)
                mat->m[i][j] = 1.0f;
            else
                mat->m[i][j] = 0.0f;
            j++;
        }
        i++;
    }
}

t_mat4 mat4_multiply(t_mat4 *a, t_mat4 *b)
{
    t_mat4	tmp;
    int		i;
    int		j;
    int		k;

    i = 0;
    while (i < 4)
	{
        j = 0;
        while (j < 4)
		{
            tmp.m[i][j] = 0.0f;
            k = 0;
            while (k < 4)
			{
                tmp.m[i][j] += a->m[i][k] * b->m[k][j];
                k++;
            }
            j++;
        }
        i++;
    }
    return (tmp);
}

void create_isometric_model(t_mat4 *model)
{
	t_mat4	rx;
    t_mat4	ry;
    float	ax;
    float	ay;
    float	cx;
    float	sx;
    float	cy;
    float	sy;

	ax = -35.264f * M_PI / 180.0f;// arctan(1/√2) = angle magique 
	ay = -45.0f * M_PI / 180.0f;
	cx = cosf(ax);
	sx = sinf(ax);
	cy = cosf(ay);
	sy = sinf(ay);
    mat4_initial(&rx);
    rx.m[1][1] = cx;
    rx.m[1][2] = sx;
    rx.m[2][1] = -sx;
    rx.m[2][2] = cx;
	//[ 1    0    0    0 ]
	//[ 0   cx  sx   0 ] 
	//[ 0   -sx   cx   0 ]
	//[ 0    0    0    1 ]
    mat4_initial(&ry);
    ry.m[0][0] = cy;
    ry.m[0][2] = -sy;
    ry.m[2][0] = sy;
    ry.m[2][2] = cy;
	//[ cy   0   -sy   0 ]
	//[  0   1    0   0 ]
	//[sy   0   cy   0 ]
	//[  0   0    0   1 ]
    *model = mat4_multiply(&ry, &rx);
}

void create_isometric_view(t_mat4 *view, t_window_render *caca)
{
    mat4_initial(view);
	view->m[3][2] = caca->y_axe;
	//view->m[3][2] = caca->y_axe;
	view->m[3][1] = caca->x_axe;
}

void create_ortho_projection(t_mat4 *proj, t_window_render *caca)
{
    mat4_initial(proj);
    proj->m[0][0] = caca->zoom;
    proj->m[1][1] = -caca->zoom / 3;
	proj->m[2][2] = caca->zoom;
    proj->m[3][0] = WIDTH / 2.0f;
    proj->m[3][1] = HEIGHT / 2.0f;
}

void	get_screen_pos(t_vec3 p, int *sx, int *sy, t_mat4 *mvp)
{
    float tx;
    float ty;

    tx = p.x * mvp->m[0][0] + p.y * mvp->m[1][0] + p.z * mvp->m[2][0] + mvp->m[3][0];
    ty = p.x * mvp->m[0][1] + p.y * mvp->m[1][1] + p.z * mvp->m[2][1] + mvp->m[3][1];
    *sx = (int)(tx);
    *sy = (int)(ty);
}

void draw_point(int cx, int cy, unsigned int color, t_window_render *caca)
{
    int	size;
    int	x;
	int	y;
	int	idx;

	size = 0;
    y = cy - size;
    while (y <= cy + size)
	{
        x = cx - size;
        while (x <= cx + size)
		{
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			{
                idx = y * WIDTH + x;
            	caca->pixels[idx].rgba = color;
            }
            x++;
        }
        y++;
    }
}

t_mat4	render_isometric(t_window_render *caca)
{
    t_mat4	model;
	t_mat4	view;
	t_mat4	proj;
	t_mat4	mv;
	t_mat4	mvp;

    create_isometric_model(&model);
    create_isometric_view(&view, caca);
    create_ortho_projection(&proj, caca);
    mv = mat4_multiply(&view, &model);
    mvp = mat4_multiply(&proj, &mv);
	return (mvp);
}

void	draw_every_point(t_window_render *caca)
{
	int		i;
    int		sx;
	int		sy;
	t_vec3	p;

	i = 0;
    while (i < WIDTH * HEIGHT)
	{
        caca->pixels[i].rgba = 0x000000FF;
		i++;
	}
	i = 0;
    while (i < caca->x_max * caca->y_max * 3)
	{
        p.x = caca->map[i];
        p.y = caca->map[i + 2];
        p.z =  caca->map[i + 1];
		get_screen_pos(p, &sx, &sy, &caca->mvp);
		//ft_printf("x : %d          ", sx);
		//ft_printf("y : %d\n", sy);
		if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
            draw_point(sx, sy, 0xE0115FFF, caca);
		i += 3;
	}
}

void key_hook(int key, void* param)
{
	if (key == 41)
		mlx_loop_end((mlx_context)param);
}

void key_zoom(int button, void* param)
{
	if (button == 1)
		*(float *)param += 1.0f;
	if (button == 2 && *(float *)param > 0)
		*(float *)param -= 1.0f;
}

void key_moove(int key, void* param)
{
	t_window_render *caca;

	caca = (t_window_render*)param;
	if (key == 4)
	{
		caca->x_axe -= 10.0f;
		caca->y_axe += 20.0f;
	}
	if (key == 7)
	{
		caca->x_axe += 10.0f;
		caca->y_axe -= 20.0f;
	}
	if (key == 22)
		caca->x_axe += 20.0f;
	if (key == 26)
		caca->x_axe -= 20.0f;
}

void update(void* param)
{
    t_window_render *caca;

	caca = (t_window_render*)param;
	mlx_clear_window(caca->mlx, caca->win, (mlx_color){ .rgba = 0x000000FF });
	caca->mvp = render_isometric(caca);
	draw_every_point(caca);
	mlx_set_image_region(caca->mlx, caca->img, 0, 0, WIDTH, HEIGHT, caca->pixels);
	mlx_put_image_to_window(caca->mlx, caca->win, caca->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_map_pars	map_pars;
	t_window_render	caca;
	mlx_window_create_info info = { 0 };
    info.title = "ENORME CACA QUI PEUT BOUGE";
    info.width = WIDTH;
    info.height = HEIGHT;
	// int	i = 0;
	if (ac != 2)
	{
		ft_printf("./fdf <map>");
		return (EXIT_FAILURE);
	}
	parse_map(av[1], &map_pars, &caca);
	if (caca.map == NULL)
	{
		ft_printf("parsing error from: %s", av[1]);
		return (EXIT_FAILURE);	
	}
	// while (i < map_pars.y_max * map_pars.x_max * 3)
	// {
	// 	ft_printf("x : %d\n", map_pars.map[i]);
	// 	ft_printf("y : %d\n", map_pars.map[i + 1]);
	// 	ft_printf("z : %d\n", map_pars.map[i + 2]);
	// 	ft_printf("\n");
	// 	i += 3;
	// }
	// i = 0;
	ft_printf("\n");
	ft_printf("\n");
	// while (i < map_pars.y_max * map_pars.x_max)
	// {
		// printf("color :%ld \n", map_pars.color_map[i]);
		// i++;
	// }
	caca.mlx = mlx_init();
    caca.win = mlx_new_window(caca.mlx, &info);
    caca.img = mlx_new_image(caca.mlx, WIDTH, HEIGHT);
	caca.zoom = 15.0f;
	caca.x_axe = 0.0f;
	caca.y_axe = -400.0f;
	mlx_set_fps_goal(caca.mlx, 60);
	mlx_on_event(caca.mlx, caca.win, MLX_KEYDOWN, key_hook, caca.mlx);
	mlx_on_event(caca.mlx, caca.win, MLX_KEYDOWN, key_moove, &caca);
	mlx_on_event(caca.mlx, caca.win, MLX_MOUSEWHEEL, key_zoom, &caca.zoom);
	mlx_add_loop_hook(caca.mlx, update, &caca);
    mlx_loop(caca.mlx);
	free_all_int_tabs(&caca);
	mlx_destroy_image(caca.mlx, caca.img);
	mlx_destroy_window(caca.mlx, caca.win);
    mlx_destroy_context(caca.mlx);
    return (0);
}