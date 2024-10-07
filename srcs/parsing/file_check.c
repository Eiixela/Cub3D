/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:17 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/07 10:24:42 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	file_check(char *file, t_map **map)
{
	int	fd;
	int	number_line_map;

	if (file_extension_check(file))
		return (1);
	fd = file_access(file);
	if (fd == -1)
		return (1);
	if (cardinal_check(fd, map))
		return (close (fd), 1);
	fd = file_access(file);
	if (color_check(fd, map))
		return (1);
	fd = file_access(file);
	number_line_map = count_line(fd);
	if (!number_line_map)
		return (close(fd), 1);
	close(fd);
	fd = file_access(file);
	if (map_check(fd, map, number_line_map))
		return (close(fd), 1);
	return (close(fd), 0);
}
