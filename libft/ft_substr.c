/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:25:56 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 10:25:58 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*subst;
	int		size;

	if (!s)
		return (NULL);
	if (len < 1 || start > ft_strlen(s))
		return (ft_calloc(1, 1));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	subst = (char *)malloc((len + 1) * sizeof(char));
	if (!subst)
		return (NULL);
	ft_strlcpy(subst, s + start, len + 1);
	return (subst);
}
