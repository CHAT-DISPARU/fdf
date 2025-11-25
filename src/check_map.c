/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:35:48 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 17:09:22 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	check_maps_nbr(char **line_split, int k)
{
	int	j;

	j = 0;
	if (line_split[k][j] == '-')
		j++;
	while (line_split[k][j] >= '0' && line_split[k][j] <= '9')
		j++;
	if (line_split[k][j])
	{
		free_all(line_split);
		return (1);
	}
	return (0);
}

int	map_valid(char	**all_line)
{
	char	**line_split;
	int		i;
	int		k;

	i = 0;
	while (all_line[i])
	{
		line_split = ft_split(all_line[i]);
		if (!line_split)
		{
			free_all(all_line);
			return (1);
		}
		k = 0;
		while (line_split[k])
		{
			if (check_maps_nbr(line_split, k) == 1)
				return (1);
			k++;
		}
		free_all(line_split);
		i++;
	}
	return (0);
}

int	split_line_map(t_map_pars *map_pars, char ***line_split, int i)
{
	*line_split = ft_split(map_pars->all_line[i]);
	if (!*line_split)
		return (1);
	return (0);
}

int	len_valid(t_map_pars *map_pars, t_window_render *data)
{
	char	**line_split;
	int		len;
	int		i;

	i = 0;
	if (!map_pars->all_line)
		return (0);
	if (split_line_map(map_pars, &line_split, i) == 1)
		return (0);
	len = ft_tabstrlen(line_split);
	free_all(line_split);
	while (map_pars->all_line[i])
	{
		if (split_line_map(map_pars, &line_split, i) == 1)
			return (0);
		if (ft_tabstrlen(line_split) != len)
		{
			free_all(line_split);
			return (0);
		}
		free_all(line_split);
		i++;
	}
	data->y_max = i;
	return (len);
}
