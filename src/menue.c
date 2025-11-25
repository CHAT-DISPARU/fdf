/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:40:54 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 18:45:05 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	print_menue(int x, int y, char *str, t_window_render *data)
{
	mlx_string_put(data->mlx, data->win, x, y,
		(mlx_color){.rgba = 0xff0000ff}, str);
}

void	create_menue(t_window_render *data)
{
	if (data->help == 1)
	{
		print_menue(10, 10, "keys:", data);
		print_menue(10, 30, "move x -> a/d", data);
		print_menue(10, 50, "move y -> w/s", data);
		print_menue(10, 70, "color -> c", data);
		print_menue(10, 90, "background color -> space", data);
		print_menue(10, 110, "rotate x left/right (arrows)", data);
		print_menue(10, 130, "rotate y up/down (arrows)", data);
		print_menue(10, 150, "rotate z [/]", data);
		print_menue(10, 170, "speed mode -> shift", data);
		print_menue(10, 190, "deph -> +/-", data);
		print_menue(10, 210, "size points -> 1/2", data);
		print_menue(10, 230, "zoom -> mouse roll", data);
		print_menue(10, 250, "line modes -> l", data);
		print_menue(10, 270, "sphere mode -> o", data);
		print_menue(10, 290, "switch projection -> i", data);
		print_menue(10, 310, "reset -> r", data);
	}
}
