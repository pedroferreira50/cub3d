/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:21:02 by pviegas-          #+#    #+#             */
/*   Updated: 2025/07/04 21:36:17 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c == 0)
		return (1);
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			i++;
		else
		{
			count++;
			while (s[i] != (char)c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	**free_on_error(char **tab, unsigned int i)
{
	while (i > 0)
	{
		free(tab[i - 1]);
		i--;
	}
	free(tab);
	return (NULL);
}

static char	*idk(const char *s, char c, char **array, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	array[index] = (char *)malloc ((i + 1) * sizeof(char));
	if (array[index] == NULL)
		return (NULL);
	while (s[j] != (char)c && s[j] != '\0')
	{
		array[index][j] = s[j];
		j++;
	}
	array[index][j] = '\0';
	return (array[index]);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	char	**sstr;

	i = 0;
	k = 0;
	sstr = (char **)malloc ((countwords(s, (char)c) + 1) * sizeof(char *));
	if (sstr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			i++;
		else
		{
			idk (&s[i], (char)c, sstr, k);
			if (sstr[k] == NULL)
				return (free_on_error(sstr, k));
			k++;
			while (s[i] != (char)c && s[i] != '\0')
				i++;
		}
	}
	sstr[k] = NULL;
	return (sstr);
}
