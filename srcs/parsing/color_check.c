/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:56:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/01 11:28:45 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	*fill_color_int(char **color, int *color_tab)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		color_tab[i] = ft_atoi(color[i]);
		if (color_tab[i] < 0 || color_tab[i] > 255)
		{
			printf("Color not in 0-255 range\n");
			return (NULL);
		}
		i++;
	}
	if (i != 3)
	{
		printf("Invalid number of color components\n");
		return (NULL);
	}
	return (color_tab);
}

static t_map	*fill_color(char *line, char *path, t_map *map)
{
	char	**color;

	if (ft_strncmp("F ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		map->floor_c = fill_color_int(color, map->floor_c);
		free_dtab(color);
		if (!map->floor_c)
			return (NULL);
	}
	else if (ft_strncmp("C ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		map->ceiling_c = fill_color_int(color, map->ceiling_c);
		free_dtab(color);
		if (!map->ceiling_c)
			return (NULL);
	}
	return (map);
}

static t_map	*found_one_color(char *line, t_map *map)
{
	char	*path;
	char	*trimmed_path;

	path = NULL;
	if (ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0)
	{
		trimmed_path = ft_strtrim(line + 2, " \t\n\r");
		if (trimmed_path)
		{
			path = ft_strdup(trimmed_path);
			free(trimmed_path);
			if (path)
			{
				map = fill_color(line, path, map);
				free(path);
				if (!map)
					return (NULL);
			}
		}
	}
	return (map);
}

bool	found_all_color(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (map->ceiling_c[i] && map->floor_c[i])
			j++;
		i++;
	}
	if (j == 3)
		return (true);
	return (false);
}

int	color_check(int fd, t_map **map)
{
	char	*line;
	bool	all_color_found;

	all_color_found = false;
	while (!all_color_found)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (map_started(line))
			return (free(line), close(fd), 1);
		line = format_line(line);
		*map = found_one_color(line, *map);
		if (!*map)
			return (free(line), close(fd), 1);
		all_color_found = found_all_color(*map);
		free(line);
	}
	while (line) //for no leaks, please leave it there
	{
		line = get_next_line(fd);
		free(line);	
	}
/* 	printf("c = %i\n", (*map)->ceiling_c[0]);
	printf("c = %i\n", (*map)->ceiling_c[1]);
	printf("c = %i\n", (*map)->ceiling_c[2]);
	printf("f = %i\n", (*map)->floor_c[0]);
	printf("f = %i\n", (*map)->floor_c[1]);
	printf("f = %i\n", (*map)->floor_c[2]); */
	return (close(fd), 0);
}
