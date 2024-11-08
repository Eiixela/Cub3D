/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:02:00 by saperrie          #+#    #+#             */
/*   Updated: 2024/11/08 10:55:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	w_key(t_data *data)
{
	double	move_speed;
	double	dx;
	double	dy;

	move_speed = MOVE_SPEED;
	dx = cos(data->map->play_pos->angle) * move_speed;
	dy = sin(data->map->play_pos->angle) * move_speed;
	move_player(data, dx, dy);
}

void	s_key(t_data *data)
{
	double	move_speed;
	double	dx;
	double	dy;

	move_speed = MOVE_SPEED;
	dx = -cos(data->map->play_pos->angle) * move_speed;
	dy = -sin(data->map->play_pos->angle) * move_speed;
	move_player(data, dx, dy);
}

void	a_key(t_data *data)
{
	double	move_speed;
	double	dx;
	double	dy;

	move_speed = MOVE_SPEED;
	dx = sin(data->map->play_pos->angle) * move_speed;
	dy = -cos(data->map->play_pos->angle) * move_speed;
	move_player(data, dx, dy);
}

void	d_key(t_data *data)
{
	double	move_speed;
	double	dx;
	double	dy;

	move_speed = MOVE_SPEED;
	dx = -sin(data->map->play_pos->angle) * move_speed;
	dy = cos(data->map->play_pos->angle) * move_speed;
	move_player(data, dx, dy);
}
