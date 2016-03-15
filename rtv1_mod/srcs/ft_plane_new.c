/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 13:13:34 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:41:33 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plane		*ft_plane_new(int coloration, double origin[3], double vec[3])
{
	t_plane		*plane;

	if ((plane = (t_plane *)malloc(1 * sizeof(t_plane))) == NULL)
		return (NULL);
	plane->color = coloration;
	plane->coord[0] = origin[0];
	plane->coord[1] = origin[1];
	plane->coord[2] = origin[2];
	plane->factor[0] = vec[0];
	plane->factor[1] = vec[1];
	plane->factor[2] = vec[2];
	return (plane);
}
