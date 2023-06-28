/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:46:16 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/28 10:52:17 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

/* 
	Searches for the occurance of c in s.
	RETURN VAL	: the pointer to the first occurence of c in s.
					PTR to \0 if not incl
	PARAM		: s: string to search, c: cahr(delimiter to find)
 */
static char	*ft_next_del(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

/* 
	Calls the approriate print-method based on the passed specifier.
	FIRST is the indicator for recursive function calls if it is the
	first time its called (recursion level 0)
	Based on specifier the data type of how to interprete the
	element in va_arg macro is determined
	Function Pointer passed to handle uppercase, lowercase
	RETURN VAL:	Number of bytes written by called method, -1 on error
	PARAM:		ptr: current element of arg list (gets increased every call)
				specifier: char which specifies the print format
 */
static int	ft_write_format(int fd, va_list args, char specifier)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (specifier == 'p')
		return (ft_puthex_fd(va_arg(args, long), HEX_LC, fd, 1));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (specifier == 'u')
		return (ft_putnbr_fd(va_arg(args, unsigned int), fd));
	else if (specifier == 'X')
		return (ft_puthex_fd(va_arg(args, unsigned int), HEX_UC, fd, 0));
	else if (specifier == 'x')
		return (ft_puthex_fd(va_arg(args, unsigned int), HEX_LC, fd, 0));
	else if (specifier == '%')
		return (ft_putchar_fd('%', fd));
	else
		return (-1);
}

/* 
	Writes the input string between '%specifier' and calls the format writer
	if a % is detected to print a element with given format. Handles errors of
	write(). Detectes if single '%' is at the end of input string.
	RETURN VAL:	number of written bytes by write(); -1 on error
	PARAMS:		format: input string to print, might included format specifiers
				list: list of elements, which were passed to variadic function
	VARIABLES:	temp: pointer to store the current pos when traversing format
						and new delemiter was found.
				ret: stores num of written bytes by format writer
				cnt: stroes total amount of written bytes
 */
static int	ft_write(int fd, const char *format, va_list list)
{
	const char	*temp;
	int			ret;
	int			cnt;

	temp = format;
	ret = 0;
	cnt = 0;
	while (*format)
	{
		format = ft_next_del(format, '%');
		if (write(fd, temp, format - temp) < 0)
			return (-1);
		cnt += format - temp;
		if (*format == 0 || *(++format) == 0)
			break ;
		ret = ft_write_format(fd, list, *format);
		if (ret < 0)
			return (-1);
		cnt += ret;
		if (*format == 0 || *(++format) == 0)
			break ;
		temp = format;
	}
	return (cnt);
}

/* 
	Variadic function which gets at least the format. 
	va_start determines the first variadic parameter after param format.
	va_end macro performs clean up for no longer used list elements.
	RETURN VAL:	number of bytes written; -1 on error
	PARAMS:		format: mandatory string passed to variadic func,
							optional variadic params
	VARIABLES:	lst: macro which contains information
						about the current element passed in arg_list
				cnt: stores num of written bytes
 */
int	ft_fd_printf(int fd, const char *format, ...)
{
	va_list		lst;
	int			cnt;

	if (!format || fd < 0)
		return (-1);
	va_start(lst, format);
	cnt = ft_write(fd, format, lst);
	va_end(lst);
	return (cnt);
}
