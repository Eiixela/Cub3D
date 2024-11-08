/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:26:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 10:55:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_player(t_point *player)
{
	player->angle = 0;
	player->dx = 0;
	player->dy = 0;
	player->x = 0;
	player->y = 0;
}

static void	init_color(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		map->ceiling_c[i] = 0;
		map->floor_c[i++] = 0;
	}
}

//TODO add error message when return NULL
bool	init_map(t_map *map)
{
	int		i;

	i = 0;
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->map = NULL;
	map->size = NULL;
	map->floor_c = malloc(sizeof(int *) * 3);
	if (!map->floor_c)
		return (false);
	map->ceiling_c = malloc(sizeof(int *) * 3);
	if (!map->ceiling_c)
		return (false);
	map->player_way = -1;
	map->play_pos = malloc(sizeof(t_point));
	if (!map->play_pos)
		return (false);
	init_player(map->play_pos);
	map->play_pos->x = 0;
	map->play_pos->y = 0;
	init_color(map);
	return (true);
}
