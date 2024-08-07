/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:34:15 by angerard          #+#    #+#             */
/*   Updated: 2024/05/07 15:32:34 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
size_t	ft_putchar(const char c);
size_t	ft_putstr(const char *s);
int		convert_pointer(void *ptr);
int		convert_hex_upper(unsigned int num);
int		convert_hex_lower(unsigned int num);
int		convert_unsigned_decimal(unsigned int num);
int		convert_integer(int num);
int		print_number(long num);
int		print_hex(unsigned long long num, char *base);

#endif
