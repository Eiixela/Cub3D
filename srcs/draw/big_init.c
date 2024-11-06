/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:07:36 by saperrie          #+#    #+#             */
/*   Updated: 2024/11/06 13:00:39 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	player_init(t_player *player)
{
	player->view_height = 32;
	player->fov = FOV;
	player->view_angle = PI * 0.5;
	return (0);
}

int	projection_plane_init(t_pplane *pplane)
{
	pplane->width = WIDTH;
	pplane->height = HEIGHT;
	pplane->center_w = (pplane->width >> 1);
	pplane->center_h = (pplane->height >> 1);
	pplane->dst_from_player = (pplane->center_w) / tan(FOV / 2);
	pplane->angle_between_rays = (double)FOV / pplane->width;
	return (0);
}

int	big_init(t_data *data, t_player *player, t_pplane *pplane, t_map *map)
{
	data->map = map;
	data_init(data);
	if (texture_init(data) == 1)
		return (1);
	if (1 == player_init(player))
		return (1);
	data->player = player;
	if (1 == projection_plane_init(pplane))
		return (1);
	data->pplane = pplane;
	return (0);
}
