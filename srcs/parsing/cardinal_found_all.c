/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_found_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:28:08 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/13 11:16:22 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	found_all_cardinal(t_map *map)
{
	if (map->north == NULL)
		return (false);
	if (map->south == NULL)
		return (false);
	if (map->west == NULL)
		return (false);
	if (map->east == NULL)
		return (false);
	return (true);
}

int	did_found_all_cardinal(bool all_car, t_map *map)
{
	if (all_car == false)
		return (1);
	if (check_access_textures(map))
		return (1);
	return (0);
}
