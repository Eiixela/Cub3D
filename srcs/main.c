/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/11 09:26:36 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_map		map;
	t_data		data;
	t_pplane	pplane;
	t_keys		keys;
	t_ray_data	ray;

	data.ray = &ray;
	data.keys = &keys;
	if (!init_map(&map))
		return (1);
	if (!parsing(ac, av, &map))
	{
		if (big_init(&data, &pplane, &map) == 1)
			return (1);
		draw_image(&data, 1);
		free_map(&map);
	}
	else
		return (printf("Error\n"), free_map(&map), 1);
	return (0);
}
