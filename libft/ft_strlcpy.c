/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:00:12 by hvayon            #+#    #+#             */
/*   Updated: 2021/10/22 22:45:30 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *scr, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	scr_len;

	i = 0;
	dst_len = ft_strlen(dst);
	scr_len = ft_strlen(scr);
	if (!dst || !scr)
		return (0);
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && i < scr_len)
		{
			dst[i] = scr[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (scr_len);
}
