/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:23:31 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 17:30:58 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	create_parallel_model(t_mat4 *model)
{
	mat4_initial(model);
}

t_mat4	render_parallel(t_window_render *data)
{
	t_all_mat4	all_mat4;

	create_parallel_model(&all_mat4.model);
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
