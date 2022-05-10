/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:57:11 by lrosby            #+#    #+#             */
/*   Updated: 2021/10/20 19:57:29 by lrosby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char const	*ft_skip(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		s = ft_skip(s, c);
		if (*s == '\0')
			return (count);
		while (*s != c && *s != '\0')
			s++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**mas;
	char	*word_end;

	if (s == NULL)
		return (NULL);
	count = ft_word_count(s, c);
	mas = malloc(sizeof(char *) * (count + 1));
	if (!mas)
		return (NULL);
	s = ft_skip(s, c);
	i = 0;
	while (*s)
	{
		word_end = ft_strchr(s, c);
		if (!word_end)
			word_end = ft_strchr(s, '\0');
		mas[i] = ft_substr(s, 0, word_end - s);
		if (!mas[i++])
			return (NULL);
		s = ft_skip(word_end, c);
	}
	mas[i] = NULL;
	return (mas);
}
