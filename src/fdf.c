/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:47:21 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/19 11:49:25 by gajanvie         ###   ########.fr       */
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
	if (!map_pars->all_line)
		return (0);
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

unsigned int byteswap32(unsigned int t)
{
	return (t >> 24 | ((t >> 8) & 0xFF00) | ((t >> 8) & 0xFF0000) | t << 24);
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
	caca->color_map = malloc (sizeof(unsigned int) * caca->y_max * caca->x_max);
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
					caca->color_map[n] = 0xFFFFFFFF;
				else
				{
					if (*(color_str - 1) == 'x')
						caca->color_map[n] = ft_atol_base(color_str, "0123456789abcdef");
					else
						caca->color_map[n] = ft_atol_base(color_str, "0123456789ABCDEF");
					caca->color_map[n] = caca->color_map[n] << 8 | 0xFF;
				}
			}
			else
				caca->color_map[n] = 0xFFFFFFFF;
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
		return ;
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
	free(caca->map_screen);
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

void create_isometric_model(t_mat4 *model, t_window_render *caca)
{
	t_mat4	rx;
    t_mat4	ry;
    float	ax;
    float	ay;
    float	cx;
    float	sx;
    float	cy;
    float	sy;

	ax = -35.264f * M_PI / 180.0f + caca->angle_y;// arctan(1/√2) = angle magique 
	ay = -45.0f * M_PI / 180.0f + caca->angle_x;
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
    proj->m[1][1] = -caca->zoom / caca->deph;
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
				if (color == 0xFFFFFFFF && caca->color_back == -1)
					caca->pixels[idx].rgba = 0x000000FF;
				else if (color == 0x000000FF && caca->color_back == 1)
					caca->pixels[idx].rgba = 0xFFFFFFFF;
				else
            		caca->pixels[idx].rgba = color;
            }
            x++;
        }
        y++;
    }
}

void mat4_rotate_y(t_mat4 *m, float angle)
{
    float	c;
    float	s;

	s = sinf(angle);
	c = cosf(angle);
    mat4_initial(m);
    m->m[0][0] =  c;
	m->m[0][2] = s;
    m->m[2][0] = -s;
	m->m[2][2] = c;
}

void mat4_rotate_x(t_mat4 *m, float angle)
{
    float	c;
	float	s;

	c = cosf(angle);
	s = sinf(angle);
    mat4_initial(m);
    m->m[1][1] =  c;
	m->m[1][2] = -s;
    m->m[2][1] =  s;
	m->m[2][2] =  c;
}

t_mat4	render_isometric(t_window_render *caca)
{
    t_mat4	model;
	t_mat4	view;
	t_mat4	proj;
	t_mat4	mvp;
	t_mat4	mv;
	//t_mat4	rotate;
	//t_mat4	rotate_x;
	//t_mat4	rotate_y;

    create_isometric_model(&model, caca);
    create_isometric_view(&view, caca);
    create_ortho_projection(&proj, caca);
	//mat4_rotate_x(&rotate_x, caca->angle_x);
	//mat4_rotate_y(&rotate_y, caca->angle_y);
	//rotate = mat4_multiply(&rotate_y, &rotate_x);
	//model = mat4_multiply(&model, &rotate);
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
		if (caca->color_back == 1)
        	caca->pixels[i].rgba = 0x000000FF;
		else
			caca->pixels[i].rgba = 0xFFFFFFFF;
		i++;
	}
	i = 0;
    while (i < caca->x_max * caca->y_max * 3)
	{
        p.x = caca->map[i];
        p.y = caca->map[i + 2];
        p.z =  caca->map[i + 1];
		get_screen_pos(p, &sx, &sy, &caca->mvp);
		if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
		{
			if (caca->color_map[i / 3] != 0x000000FF && caca->color_bool == 1)
				draw_point(sx, sy, caca->color_map[i/3], caca);
			else
				draw_point(sx, sy, 0x000000FF, caca);
			caca->map_screen[i/3 * 2] = sx;
			caca->map_screen[(i/3 * 2) + 1] = sy;
		}
		else 
		{
			caca->map_screen[i/3 * 2] = -10;
			caca->map_screen[(i/3 * 2) + 1] = -10;
		}
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
		*(float *)param += 0.5f;
	if (button == 2 && *(float *)param > 0)
		*(float *)param -= 0.5f;
}

void key_up(int key, void* param)
{
	t_window_render *caca;

	caca = (t_window_render*)param;
	caca->key_table[key] = 0;
	printf("%d\n", key);
}

void key_down(int key, void* param)
{
	t_window_render *caca;

	caca = (t_window_render*)param;
	caca->key_table[key] = 1;
}

void window_hook(int event, void* param)
{
    if(event == 0)
        mlx_loop_end((mlx_context)param);
}

void	algo_line(t_window_render *caca, int idx, int idx2, unsigned long color)
{
    t_line_algo		vars;
	int				idx_pixel;
	
	vars.x0 = caca->map_screen[idx];
	vars.y0 = caca->map_screen[idx + 1];
	vars.x1 = caca->map_screen[idx2];
	vars.y1 = caca->map_screen[idx2 + 1];
	vars.dx = abs(vars.x1 - vars.x0);
	vars.dy = abs(vars.y1 - vars.y0);
    if (vars.x0 < vars.x1)
		vars.sx = 1;
	else
		vars.sx = -1;
    if (vars.y0 < vars.y1)
		vars.sy = 1;
	else 
		vars.sy = -1;
	vars.err = vars.dx - vars.dy;
	if ((vars.x0 < 0 || vars.x1 < 0) || (vars.x0 > WIDTH || vars.x1 > WIDTH))
		return ;
	if ((vars.y0 < 0 || vars.y1 < 0) || (vars.y0 > HEIGHT || vars.y1 > HEIGHT))
		return ;
    while (1)
    {
		if (vars.x0 >= 0 && vars.x0 < WIDTH && vars.y0 >= 0 && vars.y0 < HEIGHT)
		{
        	idx_pixel = vars.y0 * WIDTH + vars.x0;
        	if (color == 0xFFFFFFFF && caca->color_back == -1)
				caca->pixels[idx_pixel].rgba = 0x000000FF;
			else if (color == 0x000000FF && caca->color_back == 1)
				caca->pixels[idx_pixel].rgba = 0xFFFFFFFF;
			else
            	caca->pixels[idx_pixel].rgba = color;
		}
		if (vars.x0 == vars.x1 && vars.y0 == vars.y1)
        	break ;
        vars.e2 = 2*vars.err;
        if (vars.e2 > (int)-vars.dy)
        {
            vars.err = vars.err - vars.dy;
            vars.x0 += vars.sx;
        }
        if (vars.e2 < (int)vars.dx) 
        {
            vars.err = vars.err + vars.dx;
            vars.y0 += vars.sy;
        }
	}
}

void	draw_vertical(t_window_render *caca)
{
	int	i;
	int	j;
	int	idx;
	int idx2;

	j = 0;
	while (j < caca->y_max)
	{
		i = 0;
		while (i < caca->x_max - 1)
		{
			idx  = (j * caca->x_max + i) * 2;
			idx2 = (j * caca->x_max + (i + 1)) * 2;
			if (caca->color_bool == 1)
				algo_line(caca, idx, idx2, caca->color_map[j * caca->x_max + i]);
			else
				algo_line(caca, idx, idx2, 0x000000FF);
			i ++;
		}
		j++;
	}
}

void	draw_horizontal(t_window_render *caca)
{
	int	i;
	int	j;
	int	idx;
	int idx2;

	j = 0;
	while (j < caca->y_max - 1)
	{
		i = 0;
		while (i < caca->x_max)
		{
			idx  = (j * caca->x_max + i) * 2;
            idx2 = ((j + 1) * caca->x_max + i) * 2;
			if (caca->color_bool == 1)
				algo_line(caca, idx, idx2, caca->color_map[j * caca->x_max + i]);
			else
				algo_line(caca, idx, idx2, 0x000000FF);
			i ++;
		}
		j++;
	}
}

void	draw_line(t_window_render *caca)
{
	if (caca->line_show == 2)
		draw_vertical(caca);
	if (caca->line_show == 1)
		draw_horizontal(caca);
	if (caca->line_show == 3)
	{
		draw_vertical(caca);
		draw_horizontal(caca);
	} 
}

void	set_data(t_window_render *caca)
{
	caca->x_axe = -WIDTH / 4;
	caca->y_axe = -HEIGHT / 4;
	caca->color_bool = 1;
	caca->color_back = 1;
	caca->line_show = 3;
	caca->deph = 10;
	caca->zoom = 15.0f;
	caca->angle_x = 0.0f;
	caca->angle_y = 0.0f;
}

void update(void* param)
{
    t_window_render *caca;
	unsigned int	color_back;

	caca = (t_window_render*)param;
	if (caca->key_table[7] == 1)
	{
		caca->x_axe -= 10.0f;
		caca->y_axe += 20.0f;
	}
	if (caca->key_table[4] == 1)
	{
		caca->x_axe += 10.0f;
		caca->y_axe -= 20.0f;
	}
	if (caca->key_table[26] == 1)
		caca->x_axe += 20.0f;
	if (caca->key_table[22] == 1)
		caca->x_axe -= 20.0f;
	if (caca->key_table[80] == 1)
		caca->angle_x += 0.1f;
	if (caca->key_table[79] == 1)
		caca->angle_x -= 0.1f;
	if (caca->key_table[82] == 1)
		caca->angle_y += 0.1f;
	if (caca->key_table[81] == 1)
		caca->angle_y -= 0.1f;
	if (caca->key_table[6] == 1 && caca->old_key_table[6] != 1)
		caca->color_bool = -caca->color_bool;
	if (caca->key_table[86] == 1 && caca->deph < 50)
		caca->deph += 1;
	if (caca->key_table[87] == 1 && caca->deph > 1)
		caca->deph -= 1;
	if (caca->key_table[44] == 1 && caca->old_key_table[44] != 1)
		caca->color_back = -caca->color_back;
	if (caca->key_table[21] == 1 && caca->old_key_table[21] != 1)
		set_data(caca);
	if (caca->key_table[15] == 1 && caca->old_key_table[15] != 1)
	{
		if (caca->line_show == 3)
			caca->line_show = 0;
		else
			caca->line_show += 1;
	}
	if (caca->color_back == 1)
		color_back = 0x000000FF;
	else
		color_back = 0xFFFFFFFF;
	mlx_clear_window(caca->mlx, caca->win, (mlx_color){ .rgba = color_back });
	caca->mvp = render_isometric(caca);
	draw_every_point(caca);
	draw_line(caca);
	mlx_set_image_region(caca->mlx, caca->img, 0, 0, WIDTH, HEIGHT, caca->pixels);
	mlx_put_image_to_window(caca->mlx, caca->win, caca->img, 0, 0);
	ft_memcpy(caca->old_key_table, caca->key_table, sizeof(caca->key_table));
}

int	main(int ac, char **av)
{
	t_map_pars	map_pars;
	t_window_render	caca;
	mlx_window_create_info info;
    info.title = "i love les femmes gechars";
    info.width = WIDTH;
    info.height = HEIGHT;
	// int	i = 0;
	if (ac != 2)
	{
		ft_printf("./fdf <map>");
		return (EXIT_FAILURE);
	}
	parse_map(av[1], &map_pars, &caca);
	if (!caca.map)
	{
		ft_printf("parsing error from: %s\n", av[1]);
		return (EXIT_FAILURE);	
	}
	caca.mlx = mlx_init();
    caca.win = mlx_new_window(caca.mlx, &info);
    caca.img = mlx_new_image(caca.mlx, WIDTH, HEIGHT);
	set_data(&caca);
	caca.map_screen = malloc(sizeof(int) * caca.x_max * caca.y_max * 2);
	if (!caca.map_screen)
	{
		free_all_int_tabs(&caca);
		mlx_destroy_image(caca.mlx, caca.img);
		mlx_destroy_window(caca.mlx, caca.win);
    	mlx_destroy_context(caca.mlx);
		return (0);
	}
	mlx_set_fps_goal(caca.mlx, 60);
	mlx_on_event(caca.mlx, caca.win, MLX_KEYDOWN, key_hook, caca.mlx);
	mlx_on_event(caca.mlx, caca.win, MLX_KEYDOWN, key_down, &caca);
	mlx_on_event(caca.mlx, caca.win, MLX_KEYUP, key_up, &caca);
	mlx_on_event(caca.mlx, caca.win, MLX_WINDOW_EVENT, window_hook, caca.mlx);
	mlx_on_event(caca.mlx, caca.win, MLX_MOUSEWHEEL, key_zoom, &caca.zoom);
	mlx_add_loop_hook(caca.mlx, update, &caca);
    mlx_loop(caca.mlx);
	free_all_int_tabs(&caca);
	mlx_destroy_image(caca.mlx, caca.img);
	mlx_destroy_window(caca.mlx, caca.win);
    mlx_destroy_context(caca.mlx);
    return (0);
}
