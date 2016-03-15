/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 15:42:17 by vlize             #+#    #+#             */
/*   Updated: 2014/11/17 14:38:52 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t	l[2];
	int		i;
	char	*str;

	i = 1;
	l[1] = 0;
	l[0] = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * (l[0] + 1));
	if (!str)
		return (NULL);
	str[l[0]] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		l[1]++;
		i = -1;
	}
	while (l[0] > l[1])
	{
		str[l[0] - 1] = ((n % 10) * i) + 48;
		n = n / 10;
		l[0]--;
	}
	return (str);
}