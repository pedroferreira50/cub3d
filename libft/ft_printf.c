/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:13:40 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/14 17:28:08 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i] != '\0')
	{
		length += ft_putchar(str[i]);
		i++;
	}
	return (length);
}

static void	findpointer(void *ptr, int *len)
{
	if ((unsigned long long)ptr == 0)
		*len += ft_putstr("(nil)");
	else
		*len += ft_base_ul((unsigned long)ptr, "0123456789abcdef");
}

static void	findformat(char c, va_list args, int *len)
{
	void	*ptr;

	if (c == 'd')
		*len += ft_base(va_arg(args, int), "0123456789");
	else if (c == 'c')
		*len += ft_putchar((char)va_arg(args, int));
	else if (c == 's')
		*len += ft_putstr((char *)va_arg(args, char *));
	else if (c == 'p')
	{
		ptr = va_arg(args, void *);
		findpointer(ptr, len);
	}
	else if (c == 'i')
		*len += ft_base(va_arg(args, int), "0123456789");
	else if (c == 'u')
		*len += ft_base_u(va_arg(args, int), "0123456789");
	else if (c == 'x')
		*len += ft_base_u((unsigned long)va_arg(args, int), "0123456789abcdef");
	else if (c == 'X')
		*len += ft_base_u((unsigned long)va_arg(args, int), "0123456789ABCDEF");
	else if (c == '%')
		*len += ft_putchar('%');
	else
		*len += ft_putchar('%') + ft_putchar(c);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		length;
	va_list	args;

	i = 0;
	length = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			findformat(str[i], args, &length);
		}
		else
			length += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (length);
}

/* int main(void)
{
	char *str = "Hello, world!";
    int num = 42;
	printf("int custom \n");
	printf("int origin \n");
	return (0);
}


int main(void)
{
    char *str = "Hello, world!";
    int num = 42;

    printf("Testing my printf implementation:\n");
    printf("%d", ft_printf("Character: %c\n", 'A'));
    ft_printf("String: %s\n", str);
    ft_printf("Decimal (d): %d\n", num);
    ft_printf("Pointer (p): %p\n", &num);
    ft_printf("Integer (i): %i\n", num);
    ft_printf("Unsigned (u): %u\n", num);
    ft_printf("Lowercase Hex (x): %x\n", num);
    ft_printf("Uppercase Hex (X): %X\n", num);
    ft_printf("Percentage (%%): %%\n");
	//ft_printf("Solo Percentage: %\n");
	//ft_printf("Undefined %y\n");

    printf("\nResults using standard printf:\n");
    printf("Character: %c\n", 'A');
    printf("String: %s\n", str);
    printf("Decimal (d): %d\n", num);
    printf("Pointer (p): %p\n", &num);
    printf("Integer (i): %i\n", num);
    printf("Unsigned (u): %u\n", num);
    printf("Lowercase Hex (x): %x\n", num);
    printf("Uppercase Hex (X): %X\n", num);
    printf("Percentage (%%): %%\n");
	//printf("Solo Percentage: %\n");
	//printf("Undefined %y\n");

    return (0);
}
 */