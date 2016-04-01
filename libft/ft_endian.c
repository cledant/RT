/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 14:05:01 by vlize             #+#    #+#             */
/*   Updated: 2015/01/26 14:05:02 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_endian(void)
{
	int	n;

	n = 1;
	if (*(char *)&n == 1)
		return (0);
	return (1);
}