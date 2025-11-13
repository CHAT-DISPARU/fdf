/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:47:21 by gajanvie          #+#    #+#             */
/*   Updated: 2025/11/13 16:06:21 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>


void	fill_str(char **tab, char *new, char ***result)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		(*result)[j] = ft_strdup(tab[j]);
		j++;
	}
	(*result)[j++] = ft_strdup(new);
	(*result)[j] = NULL;
}


int	ft_tabstrlen(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	**ft_tabstrdup(char **src)
{
	char	**cpy_src;
	int		i;

	i = 0;
	while (src[i])
		i ++;
	cpy_src = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	if (cpy_src == NULL)
		return (NULL);
	while (src[i])
	{
		cpy_src[i] = ft_strdup(src[i]);
		i ++;
	}
	cpy_src[i] = NULL;
	return (cpy_src);
}

char	**ft_realloc_tab(char **tab, char *new)
{
	char	**result;
	int		i;

	if (!tab && !new)
		return (NULL);
	if (!tab)
	{
		result = malloc(sizeof(char *) * 2);
		result[0] = ft_strdup(new);
		result[1] = NULL;
		free(new);
		return (result);
	}
	i = ft_tabstrlen(tab);
	result = (char **)malloc(sizeof(char *) * (i + 2));
	if (!result)
		return (NULL);
	fill_str(tab, new, &result);
	free_all(tab);
	free(new);
	return (result);
}

void	mess_error(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

int	map_valid(char	**all_line)
{
	char	**line_split;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	while (all_line[i])
	{
		line_split = ft_split(all_line[i]);
		if (!line_split)
		{
			free_all(all_line);
			mess_error("malloc parsing:", EXIT_FAILURE);
		}
		k = 0;
		while (line_split[k])
		{
			j = 0;
			if (line_split[i][j] == '-')
				j++;
			while (line_split[i][j] >= '0' && line_split[i][j] <= '9')
				j++;
			if (line_split[i][j])
			{
				free_all(line_split);
				return (1);
			}
			k++;
		}
		free_all(line_split);
		i++;	
	}
	return (0);
}

int	len_valid (t_map_pars *map_pars)
{
	char	**line_split;
	int		len;
	int		i;

	i = 0;
	line_split = ft_split(map_pars->all_line[i++]);
	if (!line_split)
		mess_error("malloc parsing:", EXIT_FAILURE);
	len = ft_tabstrlen(line_split);
	free_all(line_split);
	while (map_pars->all_line[i])
	{
		line_split = ft_split(map_pars->all_line[i]);
		if (!line_split)
			mess_error("malloc parsing:", EXIT_FAILURE);
		if (ft_tabstrlen(line_split) != len)
		{
			free_all(line_split);
			return (0);
		}
		free_all(line_split);
		i++;
	}
	map_pars->y_max = i;
	return (len);
}

int	**convert_int(t_map_pars *map_pars)
{	
	char	**line_split;
	int		i;
	int		k;
	int		j;
	
	i = 0;
	map_pars->map = malloc (sizeof(int *) * map_pars->y_max);
	map_pars->color_map = malloc (sizeof(long *) * map_pars->y_max);
	while (map_pars->all_line[i])
	{
		k = 0;
		map_pars->map[i] = malloc (sizeof(int) * map_pars->x_max);
		map_pars->color_map[i] = malloc (sizeof(long) * map_pars->x_max);
		line_split = ft_split(map_pars->all_line[i]);
		if (!line_split)
		{
			free_all(map_pars->all_line);
			mess_error("malloc parsing:", EXIT_FAILURE);
		}
		while (line_split[k])
		{
			j = 0;
			map_pars->map[i][k] = ft_atoi(line_split[k]);
			while (line_split[k][j] && line_split[k][j] != ',')
				j++;
			if (line_split[k][j])
				map_pars->color_map[i][k] = ft_atol(line_split[k] + j);
			else
				map_pars->color_map[i][k] = 0;
			k++;
		}
		free_all(line_split);
		i++;	
	}
	return (0);
	
}

void	parse_map(char *file, t_map_pars *map_pars)
{
	int	fd;
	char *line;

	map_pars->all_line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		mess_error("open map", 1);
	line = get_next_line(fd);
	while (line)
	{
		map_pars->all_line = ft_realloc_tab(map_pars->all_line, line);
		line = get_next_line(fd);
	}
	map_pars->x_max = len_valid(map_pars);
	if (map_pars->x_max > 0)
		map_pars->map = convert_int(map_pars);
	else 

		map_pars->map = NULL;
	free_all(map_pars->all_line);
}

void	free_all_int_tabs(t_map_pars *map_pars)
{
	int i;

	i = 0;
	while (map_pars->map[i])
	{
		free(map_pars->map[i]);
		free(map_pars->color_map[i]);
	}
	free(map_pars->map);
	free(map_pars->color_map);
}

int	main(int ac, char **av)
{
	t_map_pars map_pars;
	int i = 0;
	int j = 0;

	if (ac != 2)
	{
		ft_printf("./fdf <map>");
		return (EXIT_FAILURE);
	}
	parse_map(av[1], &map_pars);
	if (map_pars.map == NULL)
	{
		ft_printf("parsing error from: %s", av[1]);
		return (EXIT_FAILURE);	
	}
	while (map_pars.map[i])
	{
		j = 0;
		while (map_pars.map[i][j])
		{
			ft_printf("%d ", map_pars.map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	i = 0;
	ft_printf("\n");
	ft_printf("\n");
	while (map_pars.color_map[i])
	{
		j = 0;
		while (map_pars.color_map[i][j])
		{
			printf("%ld ", map_pars.color_map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	free_all_int_tabs(&map_pars);
}