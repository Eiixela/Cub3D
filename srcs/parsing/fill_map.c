/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:26:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/12 16:02:25 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	count_line(int fd)
{
	char	*line;
	int		i;
	bool	map_begun;

	map_begun = false;
	i = 1;
	line = NULL;
	while (!map_begun)
	{
		line = get_next_line(fd);
		if (!line || map_started(line) == true)
			break ;
		free(line);
	}
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (!line || map_started(line) == false)
			break ;
		i++;
	}
	return (free(line), i);
}

char	*space_in_minus(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			line[i] = -line[i];
		else
			line[i] = line[i];
		i++;
	}
	return (line);
}

static char	*fill_one_line(char *line)
{
	char	*one_line;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	one_line = malloc(sizeof(char) * (len + 1));
	if (!one_line)
		return (NULL);
	ft_strlcpy(one_line, line, len + 1);
	one_line = space_in_minus(one_line);
	return (one_line);
}

static int	fill_map(int fd, t_map *map, int number_line_map, int i)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	while (line)
	{
		temp = get_next_line(fd);
		free(line);
		line = temp;
		if (!line || map_started(line) == true)
			break ;
	}
	while (i < number_line_map && line)
	{
		map->map[i] = fill_one_line(line);
		free(line);
		if (!map->map[i])
			return (1);
		line = get_next_line(fd);
		i++;
	}
	map->map[i] = NULL;
	if (read_till_the_end_map(fd, line))
		return (1);
	return (0);
}

int	map_fill(int fd, t_map *map, int number_line_map)
{
	int	i;

	i = 0;
	map->map = ft_calloc(number_line_map + 1, sizeof(char *));
	map->size = malloc(sizeof(t_point));
	if (!map->map || !map->size)
		return (1);
	map->size->x = number_line_map;
	if (fill_map(fd, map, number_line_map, i))
		return (free_map(map), 1);
	i = 0;
	map->size->y = ft_strlen(map->map[i]);
	while (map->map[i])
	{
		if (ft_strlen(map->map[i++]) > map->size->y)
			if (map->map[i])
				map->size->y = ft_strlen(map->map[i]);
	}
	map->map = map_fill_square(map);
	if (!map->map)
		return (1);
	return (0);
}
