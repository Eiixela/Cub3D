/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:26:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/30 15:50:27 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//TODO add error message when return NULL
t_map *init_map(void)
{
	t_map	*map;
	int		i;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->map = NULL;
	map->ceiling_c = malloc(sizeof(int *) * 4);
	map->floor_c = malloc(sizeof(int *) * 4);
	if (!map->ceiling_c || !map->floor_c)
	{
		free(map);
		return (NULL);
	}
	for (i = 0; i < 4; i++)
	{
		map->ceiling_c[i] = 0;
		map->floor_c[i] = 0;
	}
	return (map);
}
