/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:22:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/05 13:55:07 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_extention_textures(char *file)
{
	char	*db_ext;

	if (file)
	{
		db_ext = ft_strnstr(file, ".xpm", ft_strlen(file));
		if (db_ext != NULL)
		{
			db_ext = db_ext + 4;
			if (*db_ext == '\0')
			{
				db_ext = ft_strnstr(db_ext, ".xpm", ft_strlen(db_ext));
				if (db_ext == NULL)
					if (ft_strncmp(file, ".xpm", ft_strlen(file)))
						return (0);
			}
		}
	}
	printf("Please use .xpm textures files\n");
	return (1);
}

static int	check_access_textures_files(char *texture_file)
{
	int	fd;

	fd = open(texture_file, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	check_access_textures(t_map *map)
{
	if (map->north)
		if (check_extention_textures(map->north) || check_access_textures_files(map->north))
			return (1);
	if (map->south)
		if (check_extention_textures(map->south) || check_access_textures_files(map->south))
			return (1);
	if (map->east)
		if (check_extention_textures(map->east) || check_access_textures_files(map->east))
			return (1);
	if (map->west)
		if (check_extention_textures(map->west) || check_access_textures_files(map->west))
			return (1);
	return (0);
}
