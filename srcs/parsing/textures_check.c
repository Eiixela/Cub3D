/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:22:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/02 13:53:58 by aljulien         ###   ########.fr       */
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

int	check_access_textures(t_map *map)
{
	if (map->north)
	{
		if (check_extention_textures(map->north)
			|| access(map->north, O_RDONLY) == -1)
			return (1);
	}
	if (map->south)
	{
		if (check_extention_textures(map->south)
			|| access(map->south, O_RDONLY) == -1)
			return (1);
	}
	if (map->west)
	{
		if (check_extention_textures(map->west)
			|| access(map->west, O_RDONLY) == -1)
			return (1);
	}
	if (map->east)
	{
		if (check_extention_textures(map->east)
			|| access(map->east, O_RDONLY) == -1)
			return (1);
	}
	return (0);
}
