/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:57:03 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 18:05:23 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	calculate_sphere(t_vec3 p,
	t_window_render *data, t_screen_coords *values)
{
	float	lon;
	float	lat;

	lon = (p.x / (data->x_max - 1)) * 2 * M_PI - M_PI;
	lat = (p.z / (data->y_max - 1)) * M_PI - M_PI / 2;
	values->x = (data->sphere_radius + p.y) * cosf(lat) * cosf(lon);
	values->z = (data->sphere_radius + p.y) * cosf(lat) * sinf(lon);
	values->y = (data->sphere_radius + p.y) * sinf(lat);
}
