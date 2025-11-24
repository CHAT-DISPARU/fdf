/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:27:02 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 14:48:22 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	init_vars_algo(t_window_render *data, t_line_algo *vars)
{
	if (vars->color == 0xFFFFFFFF && data->color_back == -1)
		vars->color = 0x000000FF;
	else if (vars->color == 0x000000FF && data->color_back == 1)
		vars->color = 0xFFFFFFFF;
	if (vars->color2 == 0xFFFFFFFF && data->color_back == -1)
		vars->color2 = 0x000000FF;
	else if (vars->color2 == 0x000000FF && data->color_back == 1)
		vars->color2 = 0xFFFFFFFF;
    if (vars->x0 < vars->x1)
		vars->sx = 1;
	else
		vars->sx = -1;
    if (vars->y0 < vars->y1)
		vars->sy = 1;
	else 
		vars->sy = -1;
	vars->err = vars->dx - vars->dy;
}

void	init_vars(t_window_render *data, int idx, int idx2, t_line_algo *vars)
{
	if (data->color_bool == 0)
	{
		vars->color = data->color_map[idx / 2];
		vars->color2 = data->color_map[idx2 / 2];
	}
	else if (data->color_bool == 1)
	{
		vars->color = data->color_map2[idx / 2];
		vars->color2 = data->color_map2[idx2 / 2];
	}
	else 
	{
		vars->color = data->color_map3[idx / 2];
		vars->color2 = data->color_map3[idx2 / 2];
	}
	vars->x0 = data->map_screen[idx];
	vars->y0 = data->map_screen[idx + 1];
	vars->x1 = data->map_screen[idx2];
	vars->y1 = data->map_screen[idx2 + 1];
	vars->dx = abs(vars->x1 - vars->x0);
	vars->dy = abs(vars->y1 - vars->y0);
	init_vars_algo(data, vars);
}

void	init_values(t_line_algo *vars, t_linear_interpolation *values)
{
	values->step = 0;
	if (vars->dx >= vars->dy)
    	values->max_step = vars->dx;
	else
		values->max_step = vars->dy;
	if (values->max_step == 0)
		values->max_step = 1;
}

void	find_new_err_corr(t_line_algo *vars)
{
	vars->e2 = 2 * vars->err;
    if (vars->e2 > (int)-vars->dy)
    {
    	vars->err = vars->err - vars->dy;
        vars->x0 += vars->sx;
    }
    if (vars->e2 < (int)vars->dx) 
    {
    	vars->err = vars->err + vars->dx;
        vars->y0 += vars->sy;
    }
}

void	algo_line(t_window_render *data, int idx, int idx2)
{
    t_line_algo				vars;
	int						idx_pixel;
	t_linear_interpolation	values;

	init_vars(data, idx, idx2, &vars);
	if ((vars.x0 < 0 || vars.x1 < 0) || (vars.x0 > WIDTH || vars.x1 > WIDTH))
		return ;
	if ((vars.y0 < 0 || vars.y1 < 0) || (vars.y0 > HEIGHT || vars.y1 > HEIGHT))
		return ;
	init_values(&vars, &values);
    while (1)
    {
		values.t = (float)values.step / (float)values.max_step;
		values.step++;
        idx_pixel = vars.y0 * WIDTH + vars.x0;
        data->pixels[idx_pixel].rgba = lerp_color(vars.color, vars.color2, values.t);
		if (vars.x0 == vars.x1 && vars.y0 == vars.y1)
        	break ;
		find_new_err_corr(&vars);
	}
}
