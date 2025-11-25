/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:41:29 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 17:28:35 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

unsigned int	find_neg_color(int z)
{
	if (z < 0 && z > -25)
		return (0x0f0065ff);
	if (z <= -25 && z > -50)
		return (0x00117aff);
	if (z <= -50 && z > -200)
		return (0x00074aff);
	if (z <= -200 && z > -400)
		return (0x410043ff);
	return (0x002836ff);
}

unsigned int	find_color(int z)
{
	if (z < 0)
		return (find_neg_color(z));
	if (z == 0)
		return (0x0080ffff);
	if (z > 0 && z < 5)
		return (0xebc300ff);
	if (z >= 5 && z < 15)
		return (0x7d2c00ff);
	if (z >= 15 && z < 25)
		return (0x725a00ff);
	if (z >= 25 && z < 35)
		return (0x32d300ff);
	if (z >= 35 && z < 65)
		return (0x005322ff);
	if (z >= 65 && z < 80)
		return (0x332900ff);
	if (z >= 80 && z < 90)
		return (0xe3ff3aff);
	if (z >= 90 && z < 115)
		return (0x6e6e6eff);
	if (z >= 115 && z < 135)
		return (3118596095U);
	return (0xffffffff);
}
