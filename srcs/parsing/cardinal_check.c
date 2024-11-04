/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:23:40 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/04 17:35:13 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_map	*fill_cardinal(char *line, char *path, t_map *map)
{
	char	*s1;

	s1 = "/home/saperrie/cmor/WIP/cub3d/";
	// s1 = "/home/aljulien/Documents/C/C4/Cub3D/";
	if (ft_strncmp("NO ", line, 3) == 0)
		map->north = ft_strjoin(s1, path);
	else if (ft_strncmp("SO ", line, 3) == 0)
		map->south = ft_strjoin(s1, path);
	else if (ft_strncmp("WE ", line, 3) == 0)
		map->west = ft_strjoin(s1, path);
	else if (ft_strncmp("EA ", line, 3) == 0)
		map->east = ft_strjoin(s1, path);
	return (map);
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
			}
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
			return ((void)read_till_the_end(fd, line), close(fd), \
				printf("Textures missing\n"), 1);
		line = format_line(line);
		found_one_cardinal(line, map);
		all_cardinal_found = found_all_cardinal(map);
		free(line);
	}
	all_cardinal_found = true;
	while (line) //for no leaks, please leave it there
	{
		line = get_next_line(fd);
		if (!cardinal_cmp(line))
			all_cardinal_found = false;
		free(line);
	}
	if (all_cardinal_found == false)
		return (printf("Multiple textures\n"), close(fd), 1);
	if (check_access_textures(map))
		return (printf("Please check permissions on textures files.\n"), close(fd), 1);
	return (close(fd), 0);
}
