/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:24:20 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 10:41:21 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	read_till_the_end_map(int fd, char *line)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (line != NULL && (ft_strcmp(line, "\n") != 0))
			return (read_till_the_end(fd, line), 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

int	read_till_the_end(int fd, char *line)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (line == NULL && (ft_strcmp(line, "\n") != 0))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

static void	pimp_strlcpy(char *dst, const char *src, int size)
{
	int	i;
	int	len;

	len = ft_strlen(src);
	i = 0;
	while (i < len && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size - 1)
		dst[i++] = -32;
	dst[i] = '\0';
}

static char	**map_allocate_square(t_map *map)
{
	char	**map_square;
	int		i;

	map_square = malloc(sizeof(char *) * (map->size->x + 2));
	if (!map_square)
		return (NULL);
	i = 0;
	while (i <= map->size->x)
	{
		map_square[i] = malloc(sizeof(char) * (map->size->y + 2));
		if (!map_square[i])
		{
			map_free_square(map_square, i);
			return (NULL);
		}
		i++;
	}
	return (map_square);
}

char	**map_fill_square(t_map *map)
{
	char	**map_square;
	int		i;
	int		j;

	map_square = map_allocate_square(map);
	if (!map_square)
		return (NULL);
	i = 0;
	while (i <= map->size->x)
	{
		if (i < map->size->x)
			pimp_strlcpy(map_square[i], map->map[i], map->size->y + 2);
		else
		{
			j = 0;
			while (j <= map->size->y)
				map_square[i][j++] = -32;
			map_square[i][j] = '\0';
		}
		i++;
	}
	map_square[i] = NULL;
	free_char_map(map);
	return (map_square);
}
