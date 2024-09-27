/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:25:00 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/27 14:26:00 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	map_started(char *line)
{
	if (ft_strncmp("1", line, 1) == 0)
		return (1);
	else if (ft_strncmp("0", line, 1) == 0)
		return (1);
	else
		return (0);
}
