/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:13:49 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/30 10:42:32 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isalnum(int c)
{
	if (c < '0')
		return (0);
	else if (c > '9' && c < 'A')
		return (0);
	else if (c > 'Z' && c < 'a')
		return (0);
	else if (c > 'z')
		return (0);
	else
		return (1);
}

char *format_line(const char *line)
{
    int i, j;
    bool space_added = false;
    char *line_formatted;

    line_formatted = malloc((ft_strlen(line) + 1) * sizeof(char));
    if (!line_formatted)
        return NULL;
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
    if (j > 0 && line_formatted[j-1] == ' ')
        j--;
    line_formatted[j] = '\0';
    return line_formatted;
}

int main(int ac, char **av)
{
	printf("line = \n%s\n", av[1]);
	printf("line = \n%s\n", format_line(av[1]));
	return (1);
}