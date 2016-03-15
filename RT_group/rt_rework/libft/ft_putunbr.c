/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 17:23:23 by vlize             #+#    #+#             */
/*   Updated: 2015/03/02 17:23:24 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr(uintmax_t n)
{
	char	c;

	c = 48;
	if (n < 10)
	{
		c += n;
		ft_putchar(c);
	}
	else
	{
		ft_putunbr(n / 10);
		c += n % 10;
		ft_putchar(c);
	}
}