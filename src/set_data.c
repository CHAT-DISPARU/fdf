/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:43:21 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 18:04:51 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	set_up_win(t_window_render *data, mlx_window_create_info info)
{
	create_window(data, &info);
	set_data(data);
	data->map_screen = malloc(sizeof(int) * data->x_max * data->y_max * 2);
	if (!data->map_screen)
	{
		clean_map_mlx(data);
		return (1);
	}
	return (0);
}

void	set_data(t_window_render *data)
{
	data->x_axe = HEIGHT / 2;
	data->y_axe = WIDTH / 2;
	data->color_bool = 0;
	data->color_back = 1;
	data->line_show = 3;
	data->deph = 0.1;
	data->sphere = -1;
	data->zoom = 15.0f;
	data->angle_x = 0.0f;
	data->angle_y = 0.0f;
	data->angle_z = 0.0f;
	data->size_points = 0;
	data->help = -1;
	if (data->x_max < data->y_max)
		data->sphere_radius = data->x_max * 0.5f;
	else
		data->sphere_radius = data->y_max * 0.5f;
	ft_memset(data->key_table, 0, sizeof(data->key_table));
}

void	create_window(t_window_render *data, mlx_window_create_info	*info)
{
	info->title = "FDF";
	info->width = WIDTH;
	info->height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, info);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->view_i = 1;
}

void	call_mlx_events(t_window_render *data)
{
	mlx_set_fps_goal(data->mlx, 60);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hook, data->mlx);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_down, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, key_up, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT,
		window_hook, data->mlx);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEWHEEL, key_zoom, data);
	mlx_add_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
	clean_map_mlx(data);
}
