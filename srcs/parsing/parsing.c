/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/16 17:39:16 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parsing(int ac, char **av, t_map *map, t_player *player)
{
	if (ac != 2)
		return (1);
	if (ac == 2)
	{
		if (file_check(av[1], map))
			return (1);
		if (map_good(map, player))
			return (1);
	}
	return (0);
}
