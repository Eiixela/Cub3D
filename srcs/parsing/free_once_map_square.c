/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_once_map_square.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:25:41 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/07 16:26:37 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_char_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
	{
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
}

void	map_free_square(char **map_square, int i)
{
	while (--i >= 0)
		free(map_square[i]);
	free(map_square);
}
