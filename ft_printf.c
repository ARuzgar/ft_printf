/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:33:12 by aerbosna          #+#    #+#             */
/*   Updated: 2023/08/08 18:33:54 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse(va_list arg, char *str)
{
	int	print_count;

	print_count = 0;
	if (*str == CHAR_FLAG)
		print_count += put_char(va_arg(arg, char));
	else if (*str == STR_FLAG)
		print_count += put_string(va_arg(arg, char *));
	else if (*str == 'i' || *str == 'd')
		print_count += print_base10(va_arg(arg, int));
	else if (*str == UNSIGNED_FLAG)
		print_count += print_unsigned(va_arg(arg, unsigned int));
	else if (*str == 'x' || *str == 'X')
		print_count += print_hex(va_arg(arg, unsigned int), *str);
	else if (*str == '%')
		print_count += write(1, "%", 1);
	else if (*str == PTR_FLAG)
	{
		print_count += write(1, "0x", 2);
		print_count += print_hex(va_arg(arg, unsigned int), *str);
	}
	return (print_count);
}

int	ft_printf(const char *string, ...)
{
	int		print_count;
	va_list	argument;

	print_count = 0;
	va_start (argument, string);
	while (*string)
	{
		if (*string == '%' && *(string + 1))
			print_count += parse(&argument, ++string);
		else
			print_count += put_char(string++);
	}
	return (print_count);
}

#include "ft_printf.h"
#include <stdio.h>

int main()
{
    int print_count;

    // Test cases for ft_printf
    printf("Unit Testing ft_printf:\n\n");

    // Test individual characters and strings
    print_count = ft_printf("Characters: %c %c\n", 'A', 'B');
    printf("ft_printf: %d\n", print_count);
    printf("printf: %d\n\n", printf("Characters: %c %c\n", 'A', 'B'));

    // Test integers and hexadecimal conversions
    print_count = ft_printf("Integers: %d %i %x %X\n", 123, -456, 255, 255);
    printf("ft_printf: %d\n", print_count);
    printf("printf: %d\n\n", printf("Integers: %d %i %x %X\n", 123, -456, 255, 255));

    // Test strings and pointers
    print_count = ft_printf("Strings and Pointers: %s %p\n", "Hello", &print_count);
    printf("ft_printf: %d\n", print_count);
    printf("printf: %d\n\n", printf("Strings and Pointers: %s %p\n", "Hello", &print_count));

    // Test percentage sign
    print_count = ft_printf("Percentage: %%\n");
    printf("ft_printf: %d\n", print_count);
    printf("printf: %d\n\n", printf("Percentage: %%\n"));

    // Test edge cases
    print_count = ft_printf("Edge Cases: %d %s %% %c\n", INT_MIN, NULL, 'Z');
    printf("ft_printf: %d\n", print_count);
    printf("printf: %d\n\n", printf("Edge Cases: %d %s %% %c\n", INT_MIN, NULL, 'Z'));

    return 0;
}