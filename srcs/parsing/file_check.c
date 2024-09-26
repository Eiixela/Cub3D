/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:17 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/26 17:16:24 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	file_access(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Please check the permission of the map\n");
		return (-1);
	}
	return (fd);
}

int	init_map(t_map *map)
{
	int	i;

	i = 0;
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->map = NULL;
	while (i < 4)
	{
		map->ceiling_c[i] = 0;
		map->floor_c[i] = 0;
		i++;
	}
	return (0);
}

//TODO texteture_access_check
int	found_one_cardinal(char *line, t_map *map)
{
	if (ft_strncmp("NO", line, 2) == 0)
	{
		line = line + 2;
		map->north = line;
	}
	else if (ft_strncmp("SO", line, 2) == 0)
	{
		line = line + 2;
		map->north = line;
	}
	else if (ft_strncmp("WE", line, 2) == 0)
	{
		line = line + 2;
		map->north = line;
	}
	else if (ft_strncmp("EA", line, 2) == 0)
	{
		line = line + 2;
		map->north = line;
	}
	else
		return (1);
	//texteture_access_check(map);
	return (0);
}

int	map_started(char *line)
{
	if (ft_strncmp("1", line, 1) == 0)
		return (1);
	else if (ft_strncmp("0", line, 1) == 0)
		return (1);
	else
		return (0);
}

bool	found_all_cardinal(t_map *map)
{
	if (!map->north)
		if (!map->south)
			if (!map->east)
				if (!map->west)
					return (true);
	return (false);
}

int	cardinal_check(int fd, t_map *map)
{
	char	*line;
	bool	all_cardinal_found;

	all_cardinal_found = false;
	if (init_map(map))
		return (1);
	while (all_cardinal_found == false)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		found_one_cardinal(line, map);
		if (map_started(line))
			return (1);
		all_cardinal_found = found_all_cardinal(map);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}

int	file_check(char *file, t_map *map)
{
	int	fd;

	if (file_extension_check(file))
		return (1);
	fd = file_access(file);
	if (fd == -1)
		return (1);
	if (cardinal_check(fd, map))
		return (1);
	return (0);
}
