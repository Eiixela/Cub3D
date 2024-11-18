/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/13 11:29:16 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parsing(int ac, char **av, t_map *map)
{
	if (ac != 2)
		return (1);
	if (ac == 2)
	{
		if (file_check(av[1], map))
			return (1);
		if (map_good(map))
			return (1);
	}
	return (0);
}
