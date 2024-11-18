/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:07:36 by saperrie          #+#    #+#             */
/*   Updated: 2024/11/11 09:58:20 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	projection_plane_init(t_pplane *pplane)
{
	pplane->width = WIDTH;
	pplane->height = HEIGHT;
	pplane->center_w = (pplane->width >> 1);
	pplane->center_h = (pplane->height >> 1);
	pplane->dst_from_player = (pplane->center_w) / tan(FOV * 0.5);
	pplane->angle_between_rays = (double)FOV / pplane->width;
	return (0);
}

int	big_init(t_data *data, t_pplane *pplane, t_map *map)
{
	data->map = map;
	data_init(data);
	if (texture_init(data) == 1)
		return (1);
	if (1 == projection_plane_init(pplane))
		return (1);
	data->pplane = pplane;
	return (0);
}
