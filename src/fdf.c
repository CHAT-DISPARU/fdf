/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:47:21 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/01 15:05:48 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	keys_pressed3(t_window_render *data)
{
	if (data->key_table[30] == 1
		&& data->old_key_table[30] != 1 && data->size_points > 0)
		data->size_points -= 1;
	if (data->key_table[31] == 1
		&& data->old_key_table[31] != 1 && data->size_points < 12)
		data->size_points += 1;
	if (data->key_table[6] == 1 && data->old_key_table[6] != 1)
	{
		if (data->color_bool == 2)
			data->color_bool = 0;
		else
			data->color_bool += 1;
	}
	if (data->key_table[11] == 1 && data->old_key_table[11] != 1)
		data->help = -data->help;
}

void	keys_pressed2(t_window_render *data)
{
	if (data->key_table[18] == 1 && data->old_key_table[18] != 1)
		data->sphere = -data->sphere;
	if (data->key_table[87] == 1 && data->deph < 30)
		data->deph += 0.005 * data->speed;
	if (data->key_table[86] == 1 && data->deph > 0.001)
		data->deph -= 0.005 * data->speed;
	if (data->key_table[44] == 1 && data->old_key_table[44] != 1)
		data->color_back = -data->color_back;
	if (data->key_table[21] == 1 && data->old_key_table[21] != 1)
		set_data(data);
	if (data->key_table[15] == 1 && data->old_key_table[15] != 1)
	{
		if (data->line_show == 3)
			data->line_show = 0;
		else
			data->line_show += 1;
	}
	if (data->key_table[12] == 1 && data->old_key_table[12] != 1)
	{
		data->view_i = -data->view_i;
		set_data(data);
	}
}

void	keys_pressed(t_window_render *data)
{
	if (data->key_table[225] == 1)
		data->speed = 5;
	else
		data->speed = 1;
	if (data->key_table[7] == 1)
		data->y_axe += 2.0f * data->speed;
	if (data->key_table[4] == 1)
		data->y_axe -= 2.0f * data->speed;
	if (data->key_table[26] == 1)
		data->x_axe += 2.0f * data->speed;
	if (data->key_table[22] == 1)
		data->x_axe -= 2.0f * data->speed;
	if (data->key_table[80] == 1)
		data->angle_y += 0.014f * data->speed;
	if (data->key_table[79] == 1)
		data->angle_y -= 0.014f * data->speed;
	if (data->key_table[82] == 1)
		data->angle_x += 0.014f * data->speed;
	if (data->key_table[81] == 1)
		data->angle_x -= 0.014f * data->speed;
	if (data->key_table[47] == 1)
		data->angle_z += 0.014f * data->speed;
}

void	update(void *param)
{
	t_window_render	*data;
	unsigned int	color_back;

	data = (t_window_render *)param;
	keys_pressed(data);
	keys_pressed2(data);
	keys_pressed3(data);
	if (data->key_table[48] == 1)
		data->angle_z -= 0.014f;
	if (data->color_back == 1)
		color_back = 0x000000FF;
	else
		color_back = 0xFFFFFFFF;
	if (data->view_i == 1)
		data->mvp = render_isometric(data);
	else
		data->mvp = render_parallel(data);
	mlx_clear_window(data->mlx, data->win, (mlx_color){.rgba = color_back});
	draw_every_point(data);
	draw_line(data);
	mlx_set_image_region(data->mlx, data->img, 0, 0,
		WIDTH, HEIGHT, data->pixels);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	create_menue(data);
	ft_memcpy(data->old_key_table, data->key_table, sizeof(data->key_table));
}

int	main(int ac, char **av)
{
	t_map_pars				*map_pars;
	t_window_render			*data;
	mlx_window_create_info	info;

	if (ac != 2)
	{
		ft_printf("./fdf <map>\n");
		return (EXIT_FAILURE);
	}
	data = malloc(sizeof(t_window_render));
	map_pars = malloc(sizeof(t_map_pars));
	ft_memset(data, 0, sizeof(t_window_render));
	ft_memset(map_pars, 0, sizeof(t_map_pars));
	ft_memset(&info, 0, sizeof(mlx_window_create_info));
	if (parse_map(av[1], map_pars, data))
	{
		free_struct(data, map_pars);
		ft_printf("Error from: %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	if (set_up_win(data, info) == 1)
		return (EXIT_FAILURE);
	call_mlx_events(data);
	free(map_pars);
	return (0);
}
