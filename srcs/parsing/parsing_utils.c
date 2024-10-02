/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:25:00 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/02 14:40:42 by aljulien         ###   ########.fr       */
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

void	finalize_formatted_line(char *line_formatted, int j)
{
	if (j > 0 && line_formatted[j - 1] == ' ')
		j--;
	line_formatted[j] = '\0';
}

char	*allocate_formatted_line(char *line)
{
	char	*line_formatted;

	line_formatted = malloc((ft_strlen(line) + 1) * sizeof(char));
	return (line_formatted);
}

void	copy_formatted_line(char *line, char *line_formatted)
{
	int		i;
	int		j;
	int		space_added;

	i = 0;
	j = 0;
	space_added = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			line_formatted[j++] = line[i];
			space_added = 0;
		}
		else if (!space_added)
		{
			line_formatted[j++] = ' ';
			space_added = 1;
		}
		i++;
	}
	finalize_formatted_line(line_formatted, j);
}

char	*format_line(char *line)
{
	char	*line_formatted;

	line_formatted = allocate_formatted_line(line);
	if (!line_formatted)
		return (NULL);
	copy_formatted_line(line, line_formatted);
	free(line);
	return (line_formatted);
}
