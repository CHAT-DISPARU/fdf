/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:30:07 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 17:19:15 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	key_hook(int key, void *param)
{
	if (key == 41)
		mlx_loop_end((mlx_context)param);
}

void	key_up(int key, void *param)
{
	t_window_render	*data;

	data = (t_window_render *)param;
	data->key_table[key] = 0;
}

void	key_down(int key, void *param)
{
	t_window_render	*data;

	data = (t_window_render *)param;
	data->key_table[key] = 1;
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end((mlx_context)param);
}

void	mouse_hook(int button, int x, int y, t_window_render *data)
{
	float	old_zoom;
	float	zoom_speed;

	zoom_speed = 1.25f;
	old_zoom = data->zoom;
	if (button == 1)
		data->zoom *= zoom_speed;
	if (button == 2)
		data->zoom /= zoom_speed;
	data->y_axe = y + (data->y_axe - y) * (data->zoom / old_zoom);
	data->x_axe = x + (data->x_axe - x) * (data->zoom / old_zoom);
}
