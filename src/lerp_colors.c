/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:46:10 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 17:29:06 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

unsigned int	lerp_color(unsigned int c1, unsigned int c2, float t)
{
	t_lerp_color	lerp;

	lerp.r1 = (c1 >> 24) & 0xFF;
	lerp.g1 = (c1 >> 16) & 0xFF;
	lerp.b1 = (c1 >> 8) & 0xFF;
	lerp.r2 = (c2 >> 24) & 0xFF;
	lerp.g2 = (c2 >> 16) & 0xFF;
	lerp.b2 = (c2 >> 8) & 0xFF;
	lerp.r = (unsigned char)(lerp.r1 + t * (lerp.r2 - lerp.r1));
	lerp.g = (unsigned char)(lerp.g1 + t * (lerp.g2 - lerp.g1));
	lerp.b = (unsigned char)(lerp.b1 + t * (lerp.b2 - lerp.b1));
	return ((lerp.r << 24) | (lerp.g << 16) | (lerp.b << 8) | 0xFF);
}
