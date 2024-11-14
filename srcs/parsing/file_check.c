/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:17 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/14 12:48:29 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	file_access(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	file_extension_check(char *file)
{
	char	*db_ext;

	if (file)
	{
		db_ext = ft_strnstr(file, ".cub", ft_strlen(file));
		if (db_ext != NULL)
		{
			db_ext = db_ext + 4;
			if (*db_ext == '\0')
			{
				db_ext = ft_strnstr(db_ext, ".cub", ft_strlen(db_ext));
				if (db_ext == NULL)
					if (ft_strcmp(file, ".cub"))
						return (0);
			}
		}
	}
	printf("Please use .cub map\n");
	return (1);
}

static int	condition_for_line(char *line, int what_use)
{
	if (what_use == 1)
	{
		if (!ft_strncmp(line, "N", 1) || !ft_strncmp(line, "S", 1) \
			|| !ft_strncmp(line, "E", 1) || !ft_strncmp(line, "W", 1)
			|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			return (0);
		return (1);
	}
	if (what_use == 2)
	{
		if (ft_isascii(*line) && (ft_strncmp(line, "N", 1) \
			|| ft_strncmp(line, "S", 1) || ft_strncmp(line, "E", 1)
				|| ft_strncmp(line, "W", 1) || ft_strncmp(line, "F", 1)
				|| ft_strncmp(line, "C", 1)))
			return (0);
		return (1);
	}
	return (1);
}

static int	line_not_allowed(char *file)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		counter;

	fd = open(file, O_RDONLY);
	counter = 0;
	line = get_next_line(fd);
	tmp = line;
	while (line != NULL)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (!condition_for_line(line, 1))
			counter++;
		else if (!condition_for_line(line, 2))
			return (free(tmp), close(fd), 1);
		free(tmp);
		line = get_next_line(fd);
		tmp = line;
	}
	close(fd);
	if (counter == 6)
		return (0);
	return (1);
}

int	file_check(char *file, t_map *map)
{
	int	fd;
	int	number_line_map;

	if (file_extension_check(file))
		return (1);
	fd = file_access(file);
	if (fd == -1)
		return (printf("Please check the permission of the map\n"), 1);
	if (line_not_allowed(file))
		return (printf("Invalid line or issue a key input\n"), close (fd), 1);
	if (cardinal_check(fd, map))
		return (printf("Issue with textures\n"), close (fd), 1);
	fd = file_access(file);
	if (color_check(fd, map))
		return (1);
	fd = file_access(file);
	number_line_map = count_line(fd);
	if (!number_line_map || number_line_map == 1)
		return (close(fd), printf("No map in file bro\n"), 1);
	close(fd);
	fd = file_access(file);
	if (map_fill(fd, map, number_line_map))
		return (close(fd), 1);
	return (close(fd), 0);
}
