/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_happening.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:56:15 by aljulien          #+#    #+#             */
/*   Updated: 2024 23:22:51 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	left_arrow(t_data *data)
{
	data->map->play_pos->angle -= ROTATION_ANGLE;
	if (data->map->play_pos->angle < 0)
		data->map->play_pos->angle += 2 * PI;
	data->map->play_pos->dx = cos(data->map->play_pos->angle) * 5;
	data->map->play_pos->dy = sin(data->map->play_pos->angle) * 5;
}

void	right_arrow(t_data *data)
{
	data->map->play_pos->angle += ROTATION_ANGLE;
	if (data->map->play_pos->angle > 2 * PI)
		data->map->play_pos->angle -= 2 * PI;
	data->map->play_pos->dx = cos(data->map->play_pos->angle) * 5;
	data->map->play_pos->dy = sin(data->map->play_pos->angle) * 5;
}

int	is_wall(t_data *data, double x, double y)
{
	if (data->map->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

int	can_move(t_data *data, double new_x, double new_y)
{
	return (!is_wall(data, new_x - PLAYER_SIZE / 2, new_y - PLAYER_SIZE / 2) \
		&& !is_wall(data, new_x + PLAYER_SIZE / 2, new_y - PLAYER_SIZE / 2) \
		&& !is_wall(data, new_x - PLAYER_SIZE / 2, new_y + PLAYER_SIZE / 2) \
		&& !is_wall(data, new_x + PLAYER_SIZE / 2, new_y + PLAYER_SIZE / 2));
}

void	move_player(t_data *data, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = data->map->play_pos->x + dx;
	new_y = data->map->play_pos->y + dy;
	if (can_move(data, new_x, new_y))
	{
		data->map->play_pos->x = new_x;
		data->map->play_pos->y = new_y;
	}
	else
	{
		if (can_move(data, new_x, data->map->play_pos->y))
			data->map->play_pos->x = new_x;
		else if (can_move(data, data->map->play_pos->x, new_y))
			data->map->play_pos->y = new_y;
	}
}
