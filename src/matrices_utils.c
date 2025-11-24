/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:15:59 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 19:45:08 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

void	get_screen_pos(t_vec3 p, int *sx, int *sy, t_window_render *data)
{
    t_screen_coords values;
    float           r;
    float           dx;
    float           dy;

	values.x = p.x;
	values.y = p.y;
	values.z = p.z;
    values.tx = values.x * data->mvp.m[0][0] + values.y * data->mvp.m[1][0] + values.z * data->mvp.m[2][0] + data->mvp.m[3][0];
    values.ty = values.x * data->mvp.m[0][1] + values.y * data->mvp.m[1][1] + values.z * data->mvp.m[2][1] + data->mvp.m[3][1];
    *sx = (int)(values.tx) + data->y_axe;
    *sy = (int)(values.ty) + data->x_axe;
    if (data->sphere == 1)
	{
        dx = *sx - data->y_axe;
        dy = *sy - data->x_axe;
        r = sqrtf(dx*dx + dy*dy);
        values.theta = atan2f(dy, dx);
        *sx = (int)(data->y_axe + cosf(values.theta) * r);
        *sy = (int)(data->x_axe + sinf(values.theta) * r);
    }
}

void create_ortho_projection(t_mat4 *proj, t_window_render *data)
{
    mat4_initial(proj);
    proj->m[0][0] = data->zoom;
    proj->m[1][1] = -data->zoom;
	proj->m[2][2] = data->zoom;
}

void key_zoom(int button, void* param)
{
	t_window_render *data;
	int				x;
	int				y;

	data = (t_window_render*)param;
	mlx_mouse_get_pos(data->mlx, &x, &y);
	if (button == 1)
		mouse_hook(1, y, x, data);
	if (button == 2)
		mouse_hook(2, y, x, data);
}
