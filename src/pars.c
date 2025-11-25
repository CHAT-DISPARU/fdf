/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:40:34 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/25 18:03:27 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	malloc_maps(t_window_render *data)
{
	data->map = malloc(sizeof(int) * data->y_max * data->x_max * 3);
	data->color_map = malloc(sizeof(unsigned int) * data->y_max * data->x_max);
	data->color_map2 = malloc(sizeof(unsigned int) * data->y_max * data->x_max);
	data->color_map3 = malloc(sizeof(unsigned int) * data->y_max * data->x_max);
	if (!data->map || !data->color_map
		|| !data->color_map2 || !data->color_map3)
	{
		cleanup_map(data);
		return (1);
	}
	return (0);
}

void	separate_color(t_window_render *data, char *coma, int n)
{
	char	*color_str;

	*coma = '\0';
	color_str = coma + 1;
	if (color_str[0] == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
		color_str += 2;
	if (*color_str == '\0')
		data->color_map[n] = 0xFFFFFFFF;
	else
	{
		if (*(color_str - 1) == 'x')
			data->color_map[n] = ft_atol_base(color_str, "0123456789abcdef");
		else if (*(color_str - 1) == 'X')
			data->color_map[n] = ft_atol_base(color_str, "0123456789ABCDEF");
		else
			data->color_map[n] = 0xFFFFFF;
		data->color_map[n] = data->color_map[n] << 8 | 0xFF;
	}
}

void	fill_every_color_maps(char **line_split,
	t_window_render *data, t_multiple_index *index)
{
	char	*coma;

	coma = ft_strchr(line_split[index->k], ',');
	if (coma)
		separate_color(data, coma, index->n);
	else
		data->color_map[index->n] = 0xFFFFFFFF;
	data->map[index->j] = index->k;
	data->map[index->j + 1] = index->i;
	data->map[index->j + 2] = ft_atoi(line_split[index->k]);
	data->color_map2[index->n] = find_color(data->map[index->j + 2]);
	data->color_map3[index->n] = rand_color();
	index->n++;
	index->j += 3;
	index->k++;
}

int	convert_int(t_map_pars *map_pars, t_window_render *data)
{
	char				**line_split;
	t_multiple_index	index;

	index.i = 0;
	index.j = 0;
	index.n = 0;
	if (malloc_maps(data) == 1)
		return (1);
	while (map_pars->all_line[index.i])
	{
		index.k = 0;
		line_split = ft_split(map_pars->all_line[index.i]);
		if (!line_split)
		{
			free_all(map_pars->all_line);
			cleanup_map(data);
			return (1);
		}
		while (line_split[index.k] && index.k < data->x_max)
			fill_every_color_maps(line_split, data, &index);
		free_all(line_split);
		index.i++;
	}
	return (0);
}

int	parse_map(char *file, t_map_pars *map_pars, t_window_render *data)
{
	int		fd;
	char	*line;

	map_pars->all_line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		map_pars->all_line = ft_realloc_tab(map_pars->all_line, line);
		free(line);
		line = get_next_line(fd);
	}
	data->x_max = len_valid(map_pars, data);
	if (check_convertion(data, map_pars) == 1)
		return (1);
	return (0);
}
