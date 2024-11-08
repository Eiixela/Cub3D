/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:20:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/11/08 10:55:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map_array(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
}

void	free_mapmap(t_map *map)
{
	if (map->map)
	{
		free_map_array(map->map, map->size->x + 1);
		free(map->map);
		map->map = NULL;
	}
}

void	free_cardinals(t_map *map)
{
	if (map->north)
	{
		free(map->north);
		map->north = NULL;
	}
	if (map->east)
	{
		free(map->east);
		map->east = NULL;
	}
	if (map->south)
	{
		free(map->south);
		map->south = NULL;
	}
	if (map->west)
	{
		free(map->west);
		map->west = NULL;
	}
	free_mapmap(map);
}

void	free_map(t_map *map)
{
	if (map)
	{
		free_cardinals(map);
		if (map->ceiling_c)
		{
			free(map->ceiling_c);
			map->ceiling_c = NULL;
		}
		if (map->floor_c)
		{
			free(map->floor_c);
			map->floor_c = NULL;
		}
		if (map->size)
		{
			free(map->size);
			map->size = NULL;
		}
		if (map->play_pos)
		{
			free(map->play_pos);
			map->play_pos = NULL;
		}
		map = NULL;
	}
}
