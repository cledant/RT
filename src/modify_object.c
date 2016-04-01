/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 08:38:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 17:16:10 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_cam(t_env *e)
{
	e->menu->obj_name = "Camera";
	e->menu->data[0] = &(e->cam->crd->x);
	e->menu->data[1] = &(e->cam->crd->y);
	e->menu->data[2] = &(e->cam->crd->z);
	e->menu->data[3] = &(e->cam->rx[0]);
	e->menu->data[4] = &(e->cam->ry[0]);
	e->menu->data[5] = &(e->cam->rz[0]);
}

static void	get_light(t_env *e, t_light *light)
{
	double i;

	i = 0;
	if (light->type == 0)
	{
		e->menu->obj_name = "Light";
		e->menu->data[0] = &(light->crd->x);
		e->menu->data[1] = &(light->crd->y);
		e->menu->data[2] = &(light->crd->z);
		e->menu->data[3] = &i;
		e->menu->data[4] = &i;
		e->menu->data[5] = &i;
	}
	else
	{
		e->menu->obj_name = "Sun";
		e->menu->data[0] = &i;
		e->menu->data[1] = &i;
		e->menu->data[2] = &i;
		e->menu->data[3] = &(light->vec->x);
		e->menu->data[4] = &(light->vec->y);
		e->menu->data[5] = &(light->vec->z);
	}
}

static void	get_obj(t_env *e, t_obj *obj)
{
	e->menu->obj_name = ft_itoa(obj->type);
	e->menu->data[0] = &(obj->crd->x);
	e->menu->data[1] = &(obj->crd->y);
	e->menu->data[2] = &(obj->crd->z);
	e->menu->data[3] = &(obj->rx[0]);
	e->menu->data[4] = &(obj->ry[0]);
	e->menu->data[5] = &(obj->rz[0]);
}

void		find_light(t_env *e)
{
	int		i;
	t_light	*tmp_light;

	i = 1;
	tmp_light = e->light_lst;
	while (tmp_light && i < e->menu->ind_elem)
	{
		i++;
		tmp_light = tmp_light->next;
	}
	get_light(e, tmp_light);
}

void		find_object(t_env *e, t_obj *obj_tmp, int i, t_obj *previous)
{
	if (obj_tmp || e->menu->ind_elem == -1)
	{
		if (obj_tmp)
			get_obj(e, obj_tmp);
		else
		{
			if (e->csg_lst == NULL)
			{
				e->menu->ind_elem = i - 1;
				get_obj(e, previous);
			}
			else
				find_csg(e, i);
		}
	}
	else
	{
		if (e->csg_lst == NULL)
		{
			e->menu->ind_elem = 0;
			get_cam(e);
		}
		else
			find_csg(e, i);
	}
}
