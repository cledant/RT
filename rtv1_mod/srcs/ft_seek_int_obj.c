/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seek_int_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 18:17:56 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:41:54 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_list		*ft_seek_int_obj(t_list *lst, t_camera *camera, double *dist,
					double dir[3])
{
	t_list	*obj_int;

	obj_int = NULL;
	while (lst != NULL)
	{
		if (lst->content_size == 0 && ft_calc_int_sphere(lst->content,
				camera, dir, dist) == 1)
			obj_int = lst;
		else if (lst->content_size == 1 && ft_calc_int_plane(lst->content,
					camera, dir, dist) == 1)
			obj_int = lst;
		else if (lst->content_size == 2 && ft_calc_int_cylinder(lst->content,
				camera, dir, dist) == 1)
			obj_int = lst;
		else if (lst->content_size == 3 && ft_calc_int_cone(lst->content,
				camera, dir, dist) == 1)
			obj_int = lst;
		lst = lst->next;
	}
	return (obj_int);
}
