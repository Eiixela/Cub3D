/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:56:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/12 15:01:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_map	*found_one_color(char *line, t_map *map, int *all_colour_found)
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
				map = fill_color(line, path, map, all_colour_found);
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

static bool	found_all_color(t_map *map)
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

static bool	search_extra_color(char *line, int fd)
{
	bool	all_color_found;

	all_color_found = true;
	while (line)
	{
		line = get_next_line(fd);
		if (!color_cmp(line))
			all_color_found = false;
		free(line);
	}
	return (all_color_found);
}

int	color_check(int fd, t_map *map)
{
	char	*line;
	int		all_color_found;

	all_color_found = 0;
	while (all_color_found != 2)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (map_started(line))
			return ((void)read_till_the_end(fd, line), \
				close(fd), printf("Missing colors\n"), 1);
		line = format_line(line);
		map = found_one_color(line, map, &all_color_found);
		if (!map)
			return ((void)read_till_the_end(fd, line), close(fd), 1);
		if (found_all_color(map))
			break ;
		free(line);
	}
	if (!search_extra_color(line, fd))
		return (free(line), printf("Multiple colors\n"), close(fd), 1);
	return (free(line), close(fd), 0);
}
