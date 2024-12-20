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

double	get_x_pos_tex(t_data *data, double ray_distance, \
	t_texture *tex_cardinal)
{
	double	tex_x;

	if (data->ray->wall_direction == EAST || data->ray->wall_direction == WEST)
		tex_x = (data->map->play_pos->y + \
			ray_distance * data->ray->ray_dir.y);
	else
		tex_x = data->map->play_pos->x + \
			ray_distance * data->ray->ray_dir.x;
	tex_x -= floor(tex_x);
	if (data->ray->wall_direction == SOUTH)
		tex_x = 1.0 - tex_x;
	tex_x = (int)(tex_x * (double)tex_cardinal->width);
	if (data->ray->wall_direction == WEST)
		tex_x = tex_cardinal->width - tex_x - 1;
	return (tex_x);
}

void	draw_texture(t_data *data, t_draw_params *draw_param, \
	t_texture *tex_cardinal, double ray_distance)
{
	t_vector2D	tex_pos;
	t_draw_tex	tex;

	tex.step = 1.0 * tex_cardinal->height / draw_param->wall_height;
	tex.tex_pos_win = (draw_param->draw_start - (HEIGHT >> 1) \
		+ (draw_param->wall_height * 0.5)) * tex.step;
	tex_pos.x = get_x_pos_tex(data, ray_distance, tex_cardinal);
	tex.y = draw_param->draw_start;
	while (++tex.y <= draw_param->draw_end)
	{
		tex_pos.y = (int)tex.tex_pos_win % tex_cardinal->height;
		tex.tex_pos_win += tex.step;
		if (draw_param->n_ray >= 0 && draw_param->n_ray < WIDTH && \
			tex.y >= 0 && tex.y < HEIGHT && tex_pos.x >= 0 \
			&& tex_pos.x < tex_cardinal->width && tex_pos.y >= 0 \
				&& tex_pos.y < tex_cardinal->height)
		{
			tex.screen_index = tex.y * data->img.line_len + draw_param->n_ray * \
				(data->img.bit_per_pixel >> 3);
			tex.tex_index = tex_pos.y * tex_cardinal->line_len + tex_pos.x \
			* (tex_cardinal->bit_per_pixel >> 3);
			(*(unsigned int *)(data->img.addr + tex.screen_index)) = \
				(*(unsigned int *)(tex_cardinal->addr + tex.tex_index));
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
		data->tex[i].ptr = mlx_xpm_file_to_image(data->mlx_ptr, texture_path, \
			&data->tex[i].width, &data->tex[i].height);
		data->tex[i].addr = mlx_get_data_addr(data->tex[i].ptr, \
			&(data->tex[i].bit_per_pixel), \
			&(data->tex[i].line_len), &(data->tex[i].endian));
		i++;
	}
	return (0);
}
