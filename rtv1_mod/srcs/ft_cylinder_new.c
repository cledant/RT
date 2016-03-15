/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 09:21:30 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:38:28 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cylinder	*ft_cylinder_new(int coloration, double origin[3], double size,
				double dir[3])
{
	t_cylinder	*cyl;

	if ((cyl = (t_cylinder *)malloc(1 * sizeof(t_cylinder))) == NULL)
		return (NULL);
	cyl->radius = size;
	cyl->color = coloration;
	cyl->coord[0] = origin[0];
	cyl->coord[1] = origin[1];
	cyl->coord[2] = origin[2];
	cyl->dir[0] = dir[0];
	cyl->dir[1] = dir[1];
	cyl->dir[2] = dir[2];
	return (cyl);
}
