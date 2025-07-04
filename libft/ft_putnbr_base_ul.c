/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_ul.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:15:06 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:24 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>

static void	ft_putchar(char c, int *count)
{
	write (1, &c, 1);
	(*count)++;
}

static unsigned long long	ft_strlen(char *str)
{
	unsigned long long	length;

	length = 0;
	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

static int	valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base == (void *)0 || base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] < 32 || base[i] > 126 || base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	printnbr(unsigned long long nbr, char *base, int *count)
{
	if (nbr >= ft_strlen(base))
		printnbr(nbr / ft_strlen(base), base, count);
	ft_putchar(base[nbr % ft_strlen(base)], count);
}

int	ft_base_ul(unsigned long long nbr, char *base)
{
	unsigned long long	l;
	int					count;

	l = nbr;
	count = 0;
	if (valid_base(base) == 0)
		return (0);
	ft_putchar('0', &count);
	ft_putchar('x', &count);
	printnbr(l, base, &count);
	return (count);
}
/*
int main(void) {

    	ft_putnbr_base(2147483647, "01");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "01");
	ft_putchar('\n');
	ft_putnbr_base(2147483647, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(2147483647, "poneyvif");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "poneyvif");
	ft_putchar('\n');
	ft_putnbr_base(2147483647, "0123456789ABCDEF");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "0123456789ABCDEF");
	ft_putchar('\n');
	ft_putnbr_base(LONG_MIN, "0123456789ABCDEF");
	ft_putchar('\n');
	ft_putnbr_base(LONG_MAX, "0123456789ABCDEF");
	ft_putchar('\n');
	ft_putnbr_base(ULONG_MAX, "0123456789ABCDEF");
	ft_putchar('\n');
	ft_putnbr_base(-ULONG_MAX, "0123456789ABCDEF");

    return (0);
}
*/
