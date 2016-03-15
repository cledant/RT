/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_ambiant.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 11:01:56 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:37:49 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_cylinder_ambiant(t_cylinder *obj)
{
	int		ambiant_color[5];

	ambiant_color[0] = (obj->color & 0xFF000000);
	ambiant_color[0] = ambiant_color[0] >> (4 * 6);
	ambiant_color[0] = ambiant_color[0] * obj->ambiant;
	ambiant_color[0] = ambiant_color[0] << (4 * 6);
	ambiant_color[1] = (obj->color & 0x00FF0000);
	ambiant_color[1] = ambiant_color[1] >> (4 * 4);
	ambiant_color[1] = ambiant_color[1] * obj->ambiant;
	ambiant_color[1] = ambiant_color[1] << (4 * 4);
	ambiant_color[2] = (obj->color & 0x0000FF00);
	ambiant_color[2] = ambiant_color[2] >> (4 * 2);
	ambiant_color[2] = ambiant_color[2] * obj->ambiant;
	ambiant_color[2] = ambiant_color[2] << (4 * 2);
	ambiant_color[3] = (obj->color & 0x000000FF);
	ambiant_color[3] = ambiant_color[3] * obj->ambiant;
	ambiant_color[4] = ambiant_color[0] + ambiant_color[1] + ambiant_color[2] +
		ambiant_color[3];
	return (ambiant_color[4]);
}
