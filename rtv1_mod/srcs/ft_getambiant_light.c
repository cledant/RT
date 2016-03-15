/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getambiant_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 18:30:48 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:38:55 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_getambiant_light(t_list *obj)
{
	int		color;

	color = 0x00000000;
	if (obj->content_size == 0)
	{
		color = ft_sphere_ambiant(obj->content);
	}
	else if (obj->content_size == 1)
	{
		color = ft_plane_ambiant(obj->content);
	}
	else if (obj->content_size == 2)
	{
		color = ft_cylinder_ambiant(obj->content);
	}
	else if (obj->content_size == 3)
	{
		color = ft_cone_ambiant(obj->content);
	}
	return (color);
}
