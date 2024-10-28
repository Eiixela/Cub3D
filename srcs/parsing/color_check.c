/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:56:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/28 17:03:13 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	count_array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	*fill_color_tab(int	*color_tab)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		color_tab[i] = -1;
		i++;
	}
	return (color_tab);
}

static int	*fill_color_int(char **color, int *color_tab)
{
	int	i;

	i = count_array_size(color);
	if (i != 3)
	{
		printf("Please check the colors presence\n");
		color_tab = fill_color_tab(color_tab);
		return (color_tab);
	}
	i = 0;
	while (i < 3)
	{
		if (color[i])
			color_tab[i] = ft_atoi(color[i]);
		i++;
	}
	return (color_tab);
}

bool	check_color_value(t_map *map)
{
	int  i;

	i = 0;
	while (i < 3)
	{
		if (256 < (map)->floor_c[i] || 0 > (map)->floor_c[i])
		{
			free_map(map);
			return (false);
		}
		if (256 < (map)->ceiling_c[i] || 0 > (map)->ceiling_c[i])
		{
			free_map(map);
			return (false);
		}
		i++;
	}
	return (true);
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
		if (!check_color_value(map))
			return (NULL);
		if (!map->floor_c)
			return (free_map(map), NULL);
	}
	else if (ft_strncmp("C ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		map->ceiling_c = fill_color_int(color, map->ceiling_c);
		free_dtab(color);
		if (!map->ceiling_c)
			return (free_map(map), NULL);
	}
	return (map);
}

static t_map	*check_for_color(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (map->ceiling_c[i] == -1 || map->floor_c[i] == -1)
			return (free_map(map), NULL);
		i++;
	}
	return (map);
}

static int	color_cmp(char *line)
{
	if (line && (ft_strncmp("F ", line, 2) == 0 \
		|| ft_strncmp("C ", line, 2) == 0))
		return (0);
	return (1);
}

static t_map	*found_one_color(char *line, t_map *map)
{
	char	*path;
	char	*trimmed_path;

	path = NULL;
	if (!color_cmp(line))
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
				map = check_for_color(map);
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

int	color_check(int fd, t_map *map)
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
			return ((void)read_till_the_end(fd, line), \
				close(fd), printf("Missing colors\n"), 1);
		line = format_line(line);
		map = found_one_color(line, map);
		if (!map)
			return ((void)read_till_the_end(fd, line), close(fd), 1);
		all_color_found = found_all_color(map);
		free(line);
	}
	all_color_found = true;
	while (line) //for no leaks, please leave it there
	{
		line = get_next_line(fd);
		if (!color_cmp(line))
			all_color_found = false;
		free(line);
	}
	if (all_color_found == false)
		return (printf("Multiple colors\n"), close(fd), 1);
	return (close(fd), 0);
}
