/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:31:51 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 18:04:17 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	read_in_urand(char	*r, char *g, char *b, int fd)
{
	char	buffer[3];

	read(fd, buffer, 3);
	*r = buffer[0];
	*g = buffer[1];
	*b = buffer[2];
	if (*r < 0)
		*r = -(*r);
	if (*g < 0)
		*g = -(*g);
	if (*b < 0)
		*b = -(*b);
}

unsigned int	rand_color(void)
{
	char	r;
	char	g;
	char	b;
	int		fd;

	fd = open ("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (0xffffffff);
	read_in_urand(&r, &g, &b, fd);
	close (fd);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}
