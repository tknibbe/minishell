/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:41:14 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:08:30 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	temp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	while (n > 9)
	{
		temp = (n % 10) + '0';
		ft_putnbr_fd((n / 10), fd);
		write(fd, &temp, 1);
		return ;
	}
	if (n <= 9)
	{
		temp = n + '0';
		write(fd, &temp, 1);
	}
}
