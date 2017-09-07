/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 19:05:09 by ihodge            #+#    #+#             */
/*   Updated: 2017/08/11 20:12:44 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		word_len(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
				&& str[i] != '\0')
			i++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
				&& str[i] != '\0')
		{
			len++;
			i++;
		}
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0')
			return (len);
	}
	return (len);
}

int		count_words(char *str)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
				&& str[i] != '\0')
			i++;
		if ((str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				&& str[i] != '\0')
			words++;
		while ((str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				&& str[i] != '\0')
			i++;
	}
	return (words);
}

char	**ft_split(char *str)
{
	char	**arr;
	int		words;
	int		wordlen;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	words = count_words(str);
	if (!(arr = (char**)malloc(sizeof(*arr) * (words + 1))))
		return (NULL);
	while (i < words)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\0')
		{
			wordlen = word_len(str);
			if (!(arr[i++] = ft_strsub(str, 0, wordlen)))
				return (NULL);
			str += wordlen;
		}
		else
			str++;
	}
	arr[i] = NULL;
	return (arr);
}
