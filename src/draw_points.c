/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:28:08 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 15:44:13 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	draw_color_points(unsigned int color, t_window_render *data, int idx)
{
	if (color == 0xFFFFFFFF && data->color_back == -1)
		data->pixels[idx].rgba = 0x000000FF;
	else if (color == 0x000000FF && data->color_back == 1)
		data->pixels[idx].rgba = 0xFFFFFFFF;
	else
        data->pixels[idx].rgba = color;
}

void draw_point(int cx, int cy, unsigned int color, t_window_render *data)
{
    int	size;
    int	x;
	int	y;
	int	idx;

	size = data->size_points;
    y = cy - size;
    while (y <= cy + size)
	{
        x = cx - size;
        while (x <= cx + size)
		{
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			{
                idx = y * WIDTH + x;
				draw_color_points(color, data, idx);
            }
            x++;
        }
        y++;
    }
}

void	fill_map_screen_draw(t_window_render *data, int sx, int sy, int i)
{
	if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
	{
		if (data->color_bool == 0)
			draw_point(sx, sy, data->color_map[i/3], data);
		else if (data->color_bool == 1)
			draw_point(sx, sy,  data->color_map2[i/3], data);
		else
			draw_point(sx, sy,  data->color_map3[i/3], data);
		data->map_screen[i/3 * 2] = sx;
		data->map_screen[(i/3 * 2) + 1] = sy;
	}
	else 
	{
		data->map_screen[i/3 * 2] = -10;
		data->map_screen[(i/3 * 2) + 1] = -10;
	}
}

void	draw_every_point(t_window_render *data)
{
	int		i;
    int		sx;
	int		sy;
	t_vec3	p;

	i = 0;
    while (i < WIDTH * HEIGHT)
	{
		if (data->color_back == 1)
        	data->pixels[i].rgba = 0x000000FF;
		else
			data->pixels[i].rgba = 0xFFFFFFFF;
		i++;
	}
	i = 0;
    while (i < data->x_max * data->y_max * 3)
	{
        p.x = data->map[i];
        p.y = data->map[i + 2] * data->deph;
        p.z =  data->map[i + 1];
		get_screen_pos(p, &sx, &sy, data);
		fill_map_screen_draw(data, sx, sy, i);
		i += 3;
	}
}
