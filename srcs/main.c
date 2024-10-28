/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/27 22:48:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map_array(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		free(map->north);
		free(map->south);
		free(map->east);
		free(map->west);
		if (map->map)
		{
			free_map_array(map->map, map->size->x + 1);
			free(map->map);
		}
		free(map->ceiling_c);
		free(map->floor_c);
		free(map->size);
		free(map->player_position);
		map = NULL;
	}
}

int	main(int ac, char **av)
{
	t_map		map;
	t_data		data;
	t_player	player;
	t_pplane	pplane;
	t_keys		keys;

	data.keys = &keys;
	if (!init_map(&map))
		return (1);
	if (!parsing(ac, av, &map, &player))
	{
		if (big_init(&data, &player, &pplane, &map) == 1)
			return (1);
		draw_new_image(&data);
		free_map(&map);
	}
	else
		return (printf("hmmm...\n"), free_map(&map), 1);
	return (0);
}
