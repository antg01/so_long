/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:28:44 by angerard          #+#    #+#             */
/*   Updated: 2024/06/20 12:32:32 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	convert_integer(int num)
{
	return (print_number((long)num));
}

int	convert_unsigned_decimal(unsigned int num)
{
	return (print_number((unsigned long)num));
}

int	convert_hex_lower(unsigned int num)
{
	return (print_hex(num, "0123456789abcdef"));
}

int	convert_hex_upper(unsigned int num)
{
	return (print_hex(num, "0123456789ABCDEF"));
}

int	convert_pointer(void *ptr)
{
	int	count;

	count = write(1, "0x", 2);
	count += print_hex((unsigned long long)ptr, "0123456789abcdef");
	return (count);
}
