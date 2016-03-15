/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendc_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 11:13:01 by vlize             #+#    #+#             */
/*   Updated: 2014/12/23 11:13:02 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendc_fd(char c, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd('\n', fd);
}
