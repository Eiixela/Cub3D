/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:26:09 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/09 15:27:00 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	read_till_the_end(int fd, char *line)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (line != NULL && (ft_strcmp(line, "\n") != 0))
		{
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return(0);
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
		if (map_started(line) == true)
		{
			i++;
			break ;
		}
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

char *space_in_minus (char *line)
{
	int		i;
	
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

	one_line = NULL;
	one_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	ft_strlcpy(one_line, line, ft_strlen(line));
	one_line = space_in_minus(one_line);
	return (one_line);
}

static int	fill_map(int fd, t_map **map, int number_line_map, int i)
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
		(*map)->map[i] = fill_one_line(line);
		free(line);
		if (!(*map)->map[i])
			return (1);
		line = get_next_line(fd);
		i++;
	}
	(*map)->map[i] = NULL;
 	if (read_till_the_end(fd, line))
		return (1);
	return (0);
}

int	map_fill(int fd, t_map **map, int number_line_map)
{
	int		i;
	
	i = 0;
	(*map)->map = malloc(sizeof(char *) * (number_line_map + 1));
	if (!(*map)->map)
		return (1);
	(*map)->map_height = number_line_map;
	if (fill_map(fd, map, number_line_map, i))
	{
		free((*map)->map);
		return (1);
	}
	i = 0;
	(*map)->map_max_lenght = ft_strlen((*map)->map[i]);
	while ((*map)->map[i])
	{
		if (ft_strlen((*map)->map[i++]) > (*map)->map_max_lenght)
			(*map)->map_max_lenght = ft_strlen((*map)->map[i]);
	}
	return (0);
}
