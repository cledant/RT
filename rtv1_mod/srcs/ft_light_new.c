/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:28:05 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:40:13 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		*ft_light_new(double loc[3], int coloration)
{
	t_light		*new;

	if ((new = (t_light *)malloc(1 * sizeof(t_light))) == NULL)
		return (NULL);
	new->coord[0] = loc[0];
	new->coord[1] = loc[1];
	new->coord[2] = loc[2];
	new->color = coloration;
	return (new);
}
