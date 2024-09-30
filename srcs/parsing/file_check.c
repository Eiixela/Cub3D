/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:17 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/30 13:54:17 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	file_access(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Please check the permission of the map\n");
		return (-1);
	}
	return (fd);
}

int	file_extension_check(char *file)
{
	char	*db_ext;

	if (file)
	{
		db_ext = ft_strnstr(file, ".cub", ft_strlen(file));
		if (db_ext != NULL)
		{
			db_ext = db_ext + 4;
			if (*db_ext == '\0')
			{
				db_ext = ft_strnstr(db_ext, ".cub", ft_strlen(db_ext));
				if (db_ext == NULL)
					if (ft_strcmp(file, ".cub"))
						return (0);
			}
		}
	}
	printf("Please use .cub map\n");
	return (1);
}

char	*remove_virgule(char *path)
{
	char	*line;
	size_t	i;
	size_t	j;

	line = malloc(ft_strlen(path + 1) * sizeof(char *));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while(path[i])
	{
		if (path[i] == ',')
			i++;
		else 
		{
			line[j] = path[i];
			i++;
			j++;
		}
	}
	while (j < ft_strlen(path + 1))
		line[j++] = '\0';
	return (line);
}

t_map *fill_color_int(char **color, t_map *map)
{
    int i;

    i = 0;
    while (color[i] && i < 3)  // Assume max 3 color components (R,G,B)
    {
        map->ceiling_c[i] = ft_atoi(color[i]);
        if (map->ceiling_c[i] < 0 || map->ceiling_c[i] > 255)
        {
            printf("Color not in 0-255 range\n");
            return (NULL);
        }
        i++;
    }
    if (i != 3)  // Ensure we have exactly 3 color components
    {
        printf("Invalid number of color components\n");
        return (NULL);
    }
    return (map);
}

t_map *fill_color(char *line, char *path, t_map *map)
{
    char **color = NULL;

    path = remove_virgule(path);
   /*  if (ft_strncmp("F ", line, 2) == 0)
    {
        color = ft_split(path, ' ');
        if (!color)
            return (NULL);
        if (!fill_color_int(color, map))
            return (NULL);
    }
    else */if (ft_strncmp("C ", line, 2) == 0)
    {
        color = ft_split(path, ' ');
        if (!color)
            return (NULL);
        if (!fill_color_int(color, map))
            return (NULL);
    }
    
    // Don't forget to free the color array after use
    // (Assuming you have a function to free a char**)
   // free_char_array(color);
    
    return (map);
}


t_map	*found_one_color(char *line, t_map *map)
{
	char *path;
    char *trimmed_path;

	path = NULL;
    if (ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0)
    {
        trimmed_path = ft_strtrim(line + 2, " \t\n\r");
        if (trimmed_path)
        {
            path = ft_strdup(trimmed_path);
            free(trimmed_path);
            if (path)
				map = fill_color(line, path, map);
        }
    }
    return (map);
}

int	color_check(int fd, t_map **map)
{
	char	*line;
	bool	all_color_found;

	all_color_found = false;
	while (!all_color_found)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (map_started(line))
			return (free(line), 1);
		line = format_line(line);
		found_one_color(line, *map);
		//all_color_found = found_all_color(*map);
		free(line);
	}
	return (0);
}

int	file_check(char *file, t_map **map)
{
	int	fd;

	if (file_extension_check(file))
		return (1);
	fd = file_access(file);
	if (fd == -1)
		return (1);
 	/* if (cardinal_check(fd, map))
		return (1); */
 	if (color_check(fd, map))
		return (1);
	return (0);
}
