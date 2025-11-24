/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_iso.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:15:03 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/24 15:27:07 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void create_isometric_model(t_mat4 *model)
{
	t_mat4	rx;
    t_mat4	ry;
	t_mat4_iso iso_mat;

	iso_mat.ax = -35.264f * M_PI / 180.0f;
	iso_mat.ay = -45.0f * M_PI / 180.0f;
	iso_mat.cx = cosf(iso_mat.ax);
	iso_mat.sx = sinf(iso_mat.ax);
	iso_mat.cy = cosf(iso_mat.ay);
	iso_mat.sy = sinf(iso_mat.ay);
    mat4_initial(&rx);
    rx.m[1][1] = iso_mat.cx;
    rx.m[1][2] = iso_mat.sx;
    rx.m[2][1] = -iso_mat.sx;
    rx.m[2][2] = iso_mat.cx;
    mat4_initial(&ry);
    ry.m[0][0] = iso_mat.cy;
    ry.m[0][2] = -iso_mat.sy;
    ry.m[2][0] = iso_mat.sy;
    ry.m[2][2] = iso_mat.cy;
    *model = mat4_multiply(&ry, &rx);
}

void create_view(t_mat4 *view)
{
	mat4_initial(view);
}

t_mat4	render_isometric(t_window_render *data)
{
	t_all_mat4	all_mat4;

    create_isometric_model(&all_mat4.model);
	if (data->sphere == 1)
		mat4_initial(&all_mat4.model);
    create_view(&all_mat4.view);
    create_ortho_projection(&all_mat4.proj, data);
	mat4_rotate_x(&all_mat4.rotate_x, data->angle_x);
	mat4_rotate_y(&all_mat4.rotate_y, data->angle_y);
	mat4_rotate_z(&all_mat4.rotate_z, data->angle_z);
	all_mat4.rotate = mat4_multiply(&all_mat4.rotate_x, &all_mat4.rotate_y);
	all_mat4.rotate = mat4_multiply(&all_mat4.rotate, &all_mat4.rotate_z);
	all_mat4.model = mat4_multiply(&all_mat4.rotate, &all_mat4.model);
    all_mat4.mv = mat4_multiply(&all_mat4.view, &all_mat4.model);
    all_mat4.mvp = mat4_multiply(&all_mat4.proj, &all_mat4.mv);
	return (all_mat4.mvp);
}
