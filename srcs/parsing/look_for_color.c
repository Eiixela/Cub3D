/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:56:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/13 14:10:14 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_map	*found_one_color(char *line, t_map *map, \
	t_vector2D *all_colour_found)
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

static bool	search_extra_color(char *line, int fd, t_vector2D *all_color_found)
{
	while (line)
	{
		line = get_next_line(fd);
		if (!color_cmp(line))
			return (false);
		free(line);
	}
	if (all_color_found->x != 1)
		return (false);
	return (true);
}

int	color_check(int fd, t_map *map)
{
	char		*line;
	t_vector2D	all_color_found;

	all_color_found.x = 0;
	all_color_found.y = 0;
	while (all_color_found.x == 0 || all_color_found.y == 0)
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
		free(line);
		if (found_all_color(map))
			break ;
	}
	if (!search_extra_color(line, fd, &all_color_found))
		return (printf("Multiple colors\n"), close(fd), 1);
	return (close(fd), 0);
}
