/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:37:17 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 14:26:32 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	cleanup_map(t_window_render *data)
{
	if (data->map)
    	free(data->map);
	if (data->color_map)
    	free(data->color_map);
	if (data->color_map2)
		free(data->color_map2);
	if (data->color_map3)
		free(data->color_map3);
    data->map = NULL;
    data->color_map = NULL;
	data->color_map2 = NULL;
	data->color_map3 = NULL;
}

void	clean_map_mlx(t_window_render *data)
{
	cleanup_map(data);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_context(data->mlx);
}
