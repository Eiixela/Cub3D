/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_tolower.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: aljulien <aljulien@student.42.fr>  +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/07 14:58:09 by aljulien  #+##+# */
/*   Updated: 2023/11/27 16:43:44 by aljulien ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
	{
		c = c + 32;
		return (c);
	}
	else
	{
		return (c);
	}
	return (c);
}
