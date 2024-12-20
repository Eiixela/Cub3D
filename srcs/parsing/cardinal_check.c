/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:23:40 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/13 11:24:25 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_map	*fill_cardinal(char *line, char *path, t_map *map)
{
	if (ft_strncmp("NO ", line, 3) == 0 && map->north == NULL)
	{
		map->north = ft_strdup(path);
		return (map);
	}
	else if (ft_strncmp("SO ", line, 3) == 0 && map->south == NULL)
	{
		map->south = ft_strdup(path);
		return (map);
	}
	else if (ft_strncmp("WE ", line, 3) == 0 && map->west == NULL)
	{
		map->west = ft_strdup(path);
		return (map);
	}
	else if (ft_strncmp("EA ", line, 3) == 0 && map->east == NULL)
	{
		map->east = ft_strdup(path);
		return (map);
	}
	return (NULL);
}

int	cardinal_cmp(char *line)
{
	if (line && (ft_strncmp("NO ", line, 3) == 0 \
		|| ft_strncmp("SO ", line, 3) == 0 \
			|| ft_strncmp("WE ", line, 3) == 0 \
			|| ft_strncmp("EA ", line, 3) == 0))
		return (0);
	return (1);
}

static t_map	*found_one_cardinal(char *line, t_map *map)
{
	char	*path;
	char	*trimmed_path;

	path = NULL;
	if (!cardinal_cmp(line))
	{
		trimmed_path = ft_strtrim(line + 3, " \t\n\r");
		if (trimmed_path)
		{
			path = ft_strdup(trimmed_path);
			free(trimmed_path);
			if (path)
			{
				map = fill_cardinal(line, path, map);
				free(path);
				if (!map)
					return (NULL);
			}
		}
	}
	return (map);
}

static bool	search_extra_cardinal(char *line, int fd)
{
	bool	all_cardinal_found;

	all_cardinal_found = true;
	while (line)
	{
		line = get_next_line(fd);
		if (!cardinal_cmp(line))
			all_cardinal_found = false;
		free(line);
	}
	return (all_cardinal_found);
}

int	cardinal_check(int fd, t_map *map)
{
	char	*line;
	bool	all_cardinal_found;

	all_cardinal_found = false;
	while (!all_cardinal_found)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (map_started(line))
			return ((void)read_till_the_end(fd, line), close(fd), 1);
		line = format_line(line);
		if (!found_one_cardinal(line, map))
			return ((void)read_till_the_end(fd, line), close(fd), 1);
		all_cardinal_found = found_all_cardinal(map);
		free(line);
	}
	all_cardinal_found = true;
	if (!search_extra_cardinal(line, fd))
		return (close(fd), 1);
	if (did_found_all_cardinal(all_cardinal_found, map))
		return (close(fd), 1);
	return (close(fd), 0);
}
