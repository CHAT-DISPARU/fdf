/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:25:13 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 17:11:36 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	draw_vertical(t_window_render *data)
{
	int	i;
	int	j;
	int	idx;
	int	idx2;

	j = 0;
	while (j < data->y_max)
	{
		i = 0;
		while (i < data->x_max - 1)
		{
			idx = (j * data->x_max + i) * 2;
			idx2 = (j * data->x_max + (i + 1)) * 2;
			algo_line(data, idx, idx2);
			i ++;
		}
		j++;
	}
}

void	draw_horizontal(t_window_render *data)
{
	int	i;
	int	j;
	int	idx;
	int	idx2;

	j = 0;
	while (j < data->y_max - 1)
	{
		i = 0;
		while (i < data->x_max)
		{
			idx = (j * data->x_max + i) * 2;
			idx2 = ((j + 1) * data->x_max + i) * 2;
			algo_line(data, idx, idx2);
			i ++;
		}
		j++;
	}
}

void	draw_line(t_window_render *data)
{
	if (data->line_show == 2)
		draw_vertical(data);
	if (data->line_show == 1)
		draw_horizontal(data);
	if (data->line_show == 3)
	{
		draw_vertical(data);
		draw_horizontal(data);
	}
}
