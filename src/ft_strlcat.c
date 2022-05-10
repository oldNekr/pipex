/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:51:18 by lrosby            #+#    #+#             */
/*   Updated: 2021/10/15 18:51:20 by lrosby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size_len;
	size_t	dest_len;

	dest_len = 0;
	while (dst[dest_len] && dest_len < dstsize)
		dest_len++;
	size_len = dest_len + ft_strlen(src);
	ft_strlcpy(dst + dest_len, src, dstsize - dest_len);
	return (size_len);
}
