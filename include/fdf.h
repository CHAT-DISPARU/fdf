/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:13:19 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/14 09:23:20 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <ft_printf.h>
# include <libft.h>
# include <get_next_line.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_map_pars
{
	int	x_max;
	int	y_max;
	char	**all_line;
	int		**map;
	unsigned long	**color_map;
}				t_map_pars;

typedef struct s_map
{
	int	x_max;
	int	y_max;
	int	**z_matrix;
}				t_map;

#endif