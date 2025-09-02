/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:12 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/13 12:23:13 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_white_space(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_first_position(char const *str, char *set)
{
	int	i;

	i = 0;
	while (str[i] && is_white_space(str[i], set))
		i++;
	return (i);
}

int	get_last_position(char const *str, char *set, int start)
{
	int	i;

	i = ft_strlen(str);
	while (i > start && is_white_space(str[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	length;
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trimmed;

	i = 0;
	start = get_first_position(s1, (char *)set);
	end = get_last_position(s1, (char *)set, start);
	length = end - start + 1;
	trimmed = (char *)malloc(length);
	if (!trimmed)
		return (NULL);
	while (start < end)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}

/*
int	main(void)
{
	char s1[] = "lorem ipsum dolor sit amet";
	printf("%s", ft_strtrim(s1, "te"));
}*/