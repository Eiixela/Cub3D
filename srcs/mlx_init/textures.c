/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:26:13 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/30 03:12:49 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_texture(t_data *data, int n_ray, int draw_start, int draw_end, double wall_height, t_texture *tex)
{
	(void)draw_end;
	int	tex_x;
	int	tex_y;
	int	screen_index;
	int	tex_index;
	int	wall_top;

	wall_top = draw_start;
	// tex_x = (n_ray % 1) * data->tex->width;
	tex_x = ((n_ray) / ((int)data->ray->map_pos.x % data->tex->width)); // still makes no sense but it's the closest I got, need to calculate equivalent of wall_top but for x axis
	while (draw_start++ <= draw_end)
	{
		tex_y = (draw_start - wall_top) * (tex->height / wall_height);
		if (n_ray >= 0 && n_ray < WIDTH && draw_start >= 0 && draw_start < HEIGHT && tex_x >= 0 && tex_x < tex->width && tex_y >= 0 && tex_y < tex->height)
		{
			screen_index = draw_start * data->img.line_len + n_ray * (data->img.bit_per_pixel / 8);
			tex_index = tex_y * tex->line_len + tex_x * (tex->bit_per_pixel / 8);
			(*(unsigned int *)(data->img.addr + screen_index)) = (*(unsigned int *)(tex->addr + tex_index));
		}
	}
}

int	texture_init(t_data *data)
{
	char	*texture_path;
	int		i;

	i = 0;
	texture_path = NULL;
	while (i < 4)
	{
		if (i == 0)
			texture_path = data->map->north;
		else if (i == 1)
			texture_path = data->map->south;
		else if (i == 2)
			texture_path = data->map->east;
		else if (i == 3)
			texture_path = data->map->west;
		printf("%s\n", texture_path); // you can remove me
		data->tex[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
			texture_path, \
			&data->tex[i].width, &data->tex[i].height);
		data->tex[i].addr = mlx_get_data_addr(data->tex[i].ptr, \
			&(data->tex[i].bit_per_pixel), \
			&(data->tex[i].line_len), &(data->tex[i].endian));
		i++;
	}
	return (0);
}
