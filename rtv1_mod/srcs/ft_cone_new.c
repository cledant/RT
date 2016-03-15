/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 10:06:08 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:36:54 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cone		*ft_cone_new(int coloration, double origin[3], double size,
				double dir[3])
{
	t_cone		*cone;

	if ((cone = (t_cone *)malloc(1 * sizeof(t_cone))) == NULL)
		return (NULL);
	cone->radius = size;
	cone->color = coloration;
	cone->coord[0] = origin[0];
	cone->coord[1] = origin[1];
	cone->coord[2] = origin[2];
	cone->dir[0] = dir[0];
	cone->dir[1] = dir[1];
	cone->dir[2] = dir[2];
	return (cone);
}
