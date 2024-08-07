/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:23:31 by angerard          #+#    #+#             */
/*   Updated: 2024/06/20 12:32:29 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	spf_handler(va_list args, const char c)
{
	size_t	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count += convert_integer(va_arg(args, int));
	else if (c == 'u')
		count += convert_unsigned_decimal(va_arg(args, unsigned int));
	else if (c == 'x')
		count += convert_hex_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		count += convert_hex_upper(va_arg(args, unsigned int));
	else if (c == 'p')
		count += convert_pointer(va_arg(args, void *));
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

static int	is_in_str(const char *s, int c)
{
	while ((char)c != *s && *s != '\0')
		s++;
	if (!*s)
		return (0);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	size_t	count;
	va_list	args;
	char	*spf_format;

	spf_format = "cspdiuxX%";
	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && is_in_str(spf_format, str[i + 1]))
		{
			count += spf_handler(args, str[i + 1]);
			i++;
		}
		else if (str[i] != '%')
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
