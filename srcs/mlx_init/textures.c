/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:26:13 by marvin            #+#    #+#             */
/*   Updated: 2024/10/28 02:26:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Change xpm_file path to absolute on your machine
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
	// 	texture_path = "/mnt/c/Users/sa5ms/42/cub3d/textures/isaac64.xpm";
	// else // (data->tex->side == 1)
	texture_path = "/mnt/c/Users/sa5ms/42/cub3d/textures/mv.xpm";
	data->tex->ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
		texture_path, \
		&data->tex->width, &data->tex->height);
	data->tex->addr = mlx_get_data_addr(data->tex->ptr, \
		&data->tex->bit_per_pixel, \
		&data->tex->line_len, &data->tex->endian);
	return (0);
}
