/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:23:40 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/01 15:36:41 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_map	*fill_cardinal(char *line, char *path, t_map *map)
{
	if (ft_strncmp("NO ", line, 3) == 0)
		map->north = path;
	else if (ft_strncmp("SO ", line, 3) == 0)
		map->south = path;
	else if (ft_strncmp("WE ", line, 3) == 0)
		map->west = path;
	else if (ft_strncmp("EA ", line, 3) == 0)
		map->east = path;
	return (map);
}

static t_map	*found_one_cardinal(char *line, t_map *map)
{
	char	*path;
	char	*trimmed_path;

	path = NULL;
	if (ft_strncmp("NO ", line, 3) == 0 || ft_strncmp("SO ", line, 3) == 0
		|| ft_strncmp("WE ", line, 3) == 0 || ft_strncmp("EA ", line, 3) == 0)
	{
		trimmed_path = ft_strtrim(line + 3, " \t\n\r");
		if (trimmed_path)
		{
			path = ft_strdup(trimmed_path);
			free(trimmed_path);
			if (path)
				map = fill_cardinal(line, path, map);
		}
	}
	return (map);
}

static bool	found_all_cardinal(t_map *map)
{
	if (map->north == NULL)
		return (false);
	else if (map->south == NULL)
		return (false);
	else if (map->west == NULL)
		return (false);
	else if (map->east == NULL)
		return (false);
	return (true);
}

//TODO leak of GNL cannot fine it tho
int	cardinal_check(int fd, t_map **map)
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
			return (free(line), close(fd), 1);
		line = format_line(line);
		found_one_cardinal(line, *map);
		all_cardinal_found = found_all_cardinal(*map);
		free(line);
	}
	if (check_access_textures(*map))
		return (close(fd), 1);
	return (close(fd), 0);
}
