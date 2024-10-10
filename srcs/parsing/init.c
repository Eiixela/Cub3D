/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:26:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/10 13:43:33 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//TODO add error message when return NULL
t_map	*init_map(void)
{
	t_map	*map;
	int		i;

	i = 0;
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->map = NULL;
	map->ceiling_c = malloc(sizeof(int *) * 3);
	map->floor_c = malloc(sizeof(int *) * 3);
	if (!map->ceiling_c || !map->floor_c)
		return (free(map), NULL);
	map->player_way = -1;
	while (i < 3)
	{
		map->ceiling_c[i] = 0;
		map->floor_c[i] = 0;
		i++;
	}
	return (map);
}
