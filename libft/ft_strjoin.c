/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:22:54 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/13 12:22:55 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;
	char	*str;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	i = 0;
	j = 0;
	str = malloc(lens1 + lens2 + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[j + i] = s2[j];
		j++;
	}
	str[j + i] = '\0';
	return (str);
}
