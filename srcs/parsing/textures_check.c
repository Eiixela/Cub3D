/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:22:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/27 14:23:07 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_extention_textures(char *file)
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

int	check_access_textures(t_map *map)
{
	if (map->north)
	{	
		if (access(map->north, O_RDONLY) == -1 || check_extention_textures(map->north))
			return (1);	
	}
	if (map->south)
	{
		
		if (access(map->south, O_RDONLY) == -1 || check_extention_textures(map->south))
			return (1);	
	}
	if (map->west)
	{
		if (access(map->west, O_RDONLY) == -1 || check_extention_textures(map->west))
			return (1);	
	}
	if (map->east)
	{	
		if (access(map->east, O_RDONLY) == -1 || check_extention_textures(map->east))
			return (1);	
	}
	return (0);
}
