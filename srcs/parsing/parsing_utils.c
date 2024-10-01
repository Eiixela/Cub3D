/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:25:00 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/01 09:18:31 by aljulien         ###   ########.fr       */
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

char	*format_line(const char *line)
{
	int		i;
	int		j;
	bool	space_added;
	char	*line_formatted;

	space_added = false;
	line_formatted = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!line_formatted)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			line_formatted[j++] = line[i];
			space_added = false;
		}
		else if (!space_added)
		{
			line_formatted[j++] = ' ';
			space_added = true;
		}
		i++;
	}
	if (j > 0 && line_formatted[j - 1] == ' ')
		j--;
	line_formatted[j] = '\0';
	return (line_formatted);
}
