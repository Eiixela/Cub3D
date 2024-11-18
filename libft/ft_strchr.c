/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:24:44 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 10:24:47 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if ((char) c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
