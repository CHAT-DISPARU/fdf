/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:40:54 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 17:08:17 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	create_menue(t_window_render *data)
{
	if (data->help == 1)
	{
		mlx_string_put(data->mlx, data->win, 10, 10, (mlx_color){ .rgba = 0xff0000ff }, "keys:");
		mlx_string_put(data->mlx, data->win, 10, 30, (mlx_color){ .rgba = 0xff0000ff }, "move x -> a/d");
		mlx_string_put(data->mlx, data->win, 10, 50, (mlx_color){ .rgba = 0xff0000ff }, "move y -> w/s");
		mlx_string_put(data->mlx, data->win, 10, 70, (mlx_color){ .rgba = 0xff0000ff }, "color -> c");
		mlx_string_put(data->mlx, data->win, 10, 90, (mlx_color){ .rgba = 0xff0000ff }, "background color -> space");
		mlx_string_put(data->mlx, data->win, 10, 110, (mlx_color){ .rgba = 0xff0000ff }, "rotate x left/right (arrows)");
		mlx_string_put(data->mlx, data->win, 10, 130, (mlx_color){ .rgba = 0xff0000ff }, "rotate y up/down (arrows)");
		mlx_string_put(data->mlx, data->win, 10, 150, (mlx_color){ .rgba = 0xff0000ff }, "rotate z [/]");
		mlx_string_put(data->mlx, data->win, 10, 170, (mlx_color){ .rgba = 0xff0000ff }, "speed mode -> shift");
		mlx_string_put(data->mlx, data->win, 10, 190, (mlx_color){ .rgba = 0xff0000ff }, "deph -> +/-");
		mlx_string_put(data->mlx, data->win, 10, 210, (mlx_color){ .rgba = 0xff0000ff }, "size points -> 1/2");
		mlx_string_put(data->mlx, data->win, 10, 230, (mlx_color){ .rgba = 0xff0000ff }, "zoom -> mouse roll");
		mlx_string_put(data->mlx, data->win, 10, 250, (mlx_color){ .rgba = 0xff0000ff }, "line modes -> l");
		mlx_string_put(data->mlx, data->win, 10, 270, (mlx_color){ .rgba = 0xff0000ff }, "sphere mode -> o");
		mlx_string_put(data->mlx, data->win, 10, 290, (mlx_color){ .rgba = 0xff0000ff }, "switch projection -> i");
		mlx_string_put(data->mlx, data->win, 10, 310, (mlx_color){ .rgba = 0xff0000ff }, "reset -> r");
	}
}
