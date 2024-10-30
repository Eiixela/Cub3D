/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:55:55 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/28 02:26:13 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	texture_init(t_data *data)
{
	char	*texture_path;

	data->tex = malloc(sizeof(t_texture));
	if (!data->tex)
		return (1);
	data->tex->width = 0;
	data->tex->height = 0;
	data->tex->bit_per_pixel = 0;
	data->tex->line_len = 0;
	data->tex->endian = 0;
	// if (data->tex->side == 0)
	 	// texture_path = "/home/aljulien/Documents/C/C4/Cub3D/textures/isaac64.xpm";
	// else // (data->tex->side == 1)
	// texture_path = "/home/saperrie/cmor/WIP/cub3d/textures/isaac64.xpm";
	texture_path = "/home/aljulien/Documents/C/C4/Cub3D/textures/isaac64.xpm";
	data->tex->ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
		texture_path, \
		&data->tex->width, &data->tex->height);
	data->tex->addr = mlx_get_data_addr(data->tex->ptr, \
		&data->tex->bit_per_pixel, \
		&data->tex->line_len, &data->tex->endian);
	return (0);
}
