/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:26:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/27 14:26:46 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map *init_map(void)
{
    t_map *map;
    int i = 0;

    map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
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
    return (map);
}
