/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:28:06 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:24:06 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	*input_string;
	int		count;
	int		return_value;

	input_string = (char *)str;
	va_start(args, str);
	count = 0;
	return_value = middle_man(args, input_string, count);
	va_end(args);
	return (return_value);
}

int	middle_man(va_list args, char *input_string, int count)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input_string[i])
	{
		if (input_string[i] == '%')
		{
			count += write_substr(input_string, j, i - j);
			count += check_flags(args, input_string, i);
			j = i + 2;
			if (input_string[i + 1] == '%')
				i++;
		}
		i++;
	}
	count += write_substr(input_string, j, i - j);
	return (count);
}

int	check_flags(va_list args, char *input_string, int i)
{
	int	count;

	i ++;
	count = 0;
	if (input_string[i] == 'c')
		count = c_conversion(va_arg(args, int));
	else if (input_string[i] == 's')
		count = s_conversion(va_arg(args, char *));
	else if (input_string[i] == 'p')
		count = p_conversion(va_arg(args, unsigned long));
	else if (input_string[i] == 'd')
		count = d_conversion(va_arg(args, int));
	else if (input_string[i] == 'i')
		count = i_conversion(va_arg(args, int));
	else if (input_string[i] == 'u')
		count = u_conversion(va_arg(args, unsigned int));
	else if (input_string[i] == 'x')
		count = lower_x_conversion(va_arg(args, int));
	else if (input_string[i] == 'X')
		count = upper_x_conversion(va_arg(args, int));
	else if (input_string[i] == '%')
		count = write(1, "%", 1);
	else if (input_string[i] != ' ')
		count = c_conversion(input_string[i]);
	return (count);
}
