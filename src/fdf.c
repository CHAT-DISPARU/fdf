/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:47:21 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/16 19:53:41 by gajanvie         ###   ########.fr       */
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

int	len_valid (t_map_pars *map_pars)
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
	map_pars->y_max = i;
	return (len);
}

void cleanup_map(t_map_pars *map_pars)
{
    free(map_pars->map);
    free(map_pars->color_map);
    map_pars->map = NULL;
    map_pars->color_map = NULL;
}

void	convert_int(t_map_pars *map_pars)
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
	map_pars->map = malloc (sizeof(int) * map_pars->y_max * map_pars->x_max * 3);
	map_pars->color_map = malloc (sizeof(long) * map_pars->y_max * map_pars->x_max);
	if (!map_pars->map || !map_pars->color_map)
	{
		if (!map_pars->color_map)
			free(map_pars->map);
        mess_error("malloc map", 1);
	}
	while (map_pars->all_line[i])
	{
		k = 0;
		line_split = ft_split(map_pars->all_line[i]);
		if (!line_split)
		{
			free_all(map_pars->all_line);
			cleanup_map(map_pars);
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
					map_pars->color_map[n] = 0xFFFFFFUL;
				else
					map_pars->color_map[n] = ft_atol_base(color_str, "0123456789abcdef");
			}
			else
				map_pars->color_map[n] = 0xFFFFFFUL;
			n++;
			map_pars->map[j] = k;
			map_pars->map[j + 1] = i;
			map_pars->map[j + 2] = ft_atoi(line_split[k]);
			j += 3;
			k++;
		}
		free_all(line_split);
		i++;	
	}
}

void	parse_map(char *file, t_map_pars *map_pars)
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
	map_pars->x_max = len_valid(map_pars);
	if (map_pars->x_max > 0)
		convert_int(map_pars);
	else 

		map_pars->map = NULL;
	free_all(map_pars->all_line);
}

void	free_all_int_tabs(t_map_pars *map_pars)
{
	free(map_pars->map);
	free(map_pars->color_map);
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
    rx.m[1][2] = -sx;
    rx.m[2][1] = sx;
    rx.m[2][2] = cx;
	//[ 1    0    0    0 ]
	//[ 0   cx  -sx   0 ] iverse de wiki prcq on chqnge z et y
	//[ 0   sx   cx   0 ]
	//[ 0    0    0    1 ]
    mat4_initial(&ry);
    ry.m[0][0] = cy;
    ry.m[0][2] = sy;
    ry.m[2][0] = -sy;
    ry.m[2][2] = cy;
	//[ cy   0   sy   0 ]
	//[  0   1    0   0 ] pareil le sang
	//[-sy   0   cy   0 ]
	//[  0   0    0   1 ]
    *model = mat4_multiply(&ry, &rx);
}

void create_isometric_view(t_mat4 *view)
{
    mat4_initial(view);
    view->m[3][2] = -100.0f;
}

void create_ortho_projection(t_mat4 *proj)
{
    mat4_initial(proj);
    //proj->m[0][0] = 2.0f / WIDTH;
    //proj->m[1][1] = 2.0f / HEIGHT;
	proj->m[0][0] = 15.0f;
	proj->m[1][1] = 15.0f;
}

void	get_screen_pos(t_vec3 p, int *sx, int *sy, t_mat4 *mvp)
{
    float tx;
    float ty;

    tx = p.x * mvp->m[0][0] + p.y * mvp->m[1][0] + p.z * mvp->m[2][0] + mvp->m[3][0];
    ty = p.x * mvp->m[0][1] + p.y * mvp->m[1][1] + p.z * mvp->m[2][1] + mvp->m[3][1];
    *sx = (int)(tx + WIDTH / 2);
    *sy = (int)(ty + HEIGHT / 2);
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

void render_isometric(t_map_pars *map_pars, t_window_render *caca)
{
    t_mat4	model;
	t_mat4	view;
	t_mat4	proj;
	t_mat4	mv;
	t_mat4	mvp;
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
    create_isometric_model(&model);
    create_isometric_view(&view);
    create_ortho_projection(&proj);
    mv = mat4_multiply(&view, &model);
    mvp = mat4_multiply(&proj, &mv);
    i = 0;
    while (i < map_pars->x_max * map_pars->y_max * 3)
	{
        p.x = map_pars->map[i] - 20;
        p.y = map_pars->map[i + 1] - 20;
        p.z =  map_pars->map[i + 2];
		get_screen_pos(p, &sx, &sy, &mvp);
		ft_printf("x : %d          ", sx);
		ft_printf("y : %d\n", sy);
		if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
            draw_point(sx, sy, 0xF40210FF, caca);
		i += 3;
	}
	mlx_set_image_region(caca->mlx, caca->img, 0, 0, WIDTH, HEIGHT, caca->pixels);
    mlx_put_image_to_window(caca->mlx, caca->win, caca->img, 0, 0);
}

void key_hook(int key, void* param)
{
    if(key == 41)
        mlx_loop_end((mlx_context)param);
}

int	main(int ac, char **av)
{
	t_map_pars	map_pars;
	t_window_render	caca;
	mlx_window_create_info info = { 0 };
    info.title = "ENORME CACA";
    info.width = WIDTH;
    info.height = HEIGHT;
	// int	i = 0;
	if (ac != 2)
	{
		ft_printf("./fdf <map>");
		return (EXIT_FAILURE);
	}
	parse_map(av[1], &map_pars);
	if (map_pars.map == NULL)
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
	mlx_set_fps_goal(caca.mlx, 60);
	render_isometric (&map_pars, &caca);
	mlx_on_event(caca.mlx, caca.win, MLX_KEYDOWN, key_hook, caca.mlx);
    mlx_loop(caca.mlx);
	free_all_int_tabs(&map_pars);
	mlx_destroy_image(caca.mlx, caca.img);
	mlx_destroy_window(caca.mlx, caca.win);
    mlx_destroy_context(caca.mlx);
    return (0);
}