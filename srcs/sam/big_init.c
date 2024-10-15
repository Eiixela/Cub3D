/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:07:36 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/15 18:47:08 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	player_init(t_player *player)
{
	player->view_height = 32;
	player->fov = 60;
	player->view_angle = 270; // 270 == S; N == 90; W == 180; E == 0
	return (0);
}

int	projection_plane_init(t_pplane *pplane, t_player *player)
{
	pplane->width = 320;
	pplane->height = 200;
	pplane->center_w = (pplane->width >> 1);
	pplane->center_h = (pplane->height >> 1);
	pplane->distance_from_player = (pplane->center_w) / tan(player->fov >> 1);
	pplane->angle_between_rays = (float)player->fov / pplane->width;
	printf("%f\n", pplane->angle_between_rays);
	return (0);
}

int	big_init(t_data *data, t_player *player, t_pplane *pplane)
{
	data_init(data);
	if (1 == player_init(player))
		return (1);
	if (1 == projection_plane_init(pplane, player))
		return (1);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}
