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

double	get_x_pos_tex(t_data *data, double ray_distance)
{
	double	tex_x;

	if (data->ray->wall_direction == EAST || data->ray->wall_direction == WEST)
		tex_x = (data->map->player_position->y + \
			ray_distance * data->ray->ray_dir.y);
	else
		tex_x = data->map->player_position->x + \
			ray_distance * data->ray->ray_dir.x;
	tex_x -= floor(tex_x);
	if (data->ray->wall_direction == SOUTH)
		tex_x = 1.0 - tex_x;
	tex_x = (int)(tex_x * (double)data->tex->width);
	if (data->ray->wall_direction == WEST)
		tex_x = data->tex->width - tex_x - 1;
	return (tex_x);
}

static void    draw_texture_part(t_data *data, t_draw_params *params,
    t_vector2D tex_pos, int y)
{
    int    screen_index;
    int    tex_index;

    if (params->n_ray >= 0 && params->n_ray < WIDTH && y >= 0 && y < HEIGHT &&
        tex_pos.x >= 0 && tex_pos.x < data->tex->width &&
        tex_pos.y >= 0 && tex_pos.y < data->tex->height)
    {
        screen_index = y * data->img.line_len + params->n_ray *
            (data->img.bit_per_pixel / 8);
        tex_index = (int)tex_pos.y * data->tex->line_len + (int)tex_pos.x *
            (data->tex->bit_per_pixel / 8);
        (*(unsigned int *)(data->img.addr + screen_index)) =
            (*(unsigned int *)(data->tex->addr + tex_index));
    }
}

void    draw_texture(t_data *data, t_draw_params *params, t_texture *tex)
{
    t_vector2D    tex_pos;
    double        step;
    double        tex_pos_win;
    int            y;
	(void)tex;

    step = 1.0 * data->tex->height / params->wall_height;
    tex_pos_win = (params->draw_start - HEIGHT / 2 + params->wall_height / 2) *
        step;
    tex_pos.x = get_x_pos_tex(data, params->ray_distance);
    y = params->draw_start;
    while (y <= params->draw_end)
    {
        tex_pos.y = fmod(tex_pos_win, data->tex->height);
        tex_pos_win += step;
        draw_texture_part(data, params, tex_pos, y);
        y++;
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
