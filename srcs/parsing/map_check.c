/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:26:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/01 16:37:33 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	read_till_the_end(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
}

int	count_line(int fd)
{
	char	*line;
	int		i;
	bool	map_begun;

	map_begun = false;
	i = 0;
	line = NULL;
	while (!map_begun)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_begun = map_started(line);
		if (map_begun == true)
			break ;
		free(line);
	}
	free(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
	return (free(line), i);
}

static char	*fill_one_line(char *line)
{
	char	*one_line;

	one_line = malloc(sizeof(char) * ft_strlen(line) + 1);
	ft_strlcpy(one_line, line, ft_strlen(line));
	return (one_line);
}

static t_map	*fill_map(int fd, t_map *map, int number_line_map, int i)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	while (line)
	{
		temp = get_next_line(fd);
		free(line);
		line = temp;
		if (!line)
			break ;
		if (map_started(line) == true)
			break ;
	}
	while (i < number_line_map && line)
	{
		map->map[i] = fill_one_line(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	read_till_the_end(fd);
	return (map);
}

int	map_check(int fd, t_map **map, int number_line_map)
{
	int		i;

	i = 0;
	(*map)->map = malloc(sizeof(char *) * (number_line_map + 1));
	if (!(*map)->map)
		return (1);
	(*map)->map_height = number_line_map;
	(*map) = fill_map(fd, (*map), number_line_map, i);
	if ((*map) == NULL)
	{
		free((*map)->map);
		return (1);
	}
	return (0);
}
