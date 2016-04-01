/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 09:27:24 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 16:19:39 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		check_lights_sub(t_light *light_lst)
{
	t_light	*tmp;

	tmp = light_lst;
	while (tmp)
	{
		if (!tmp->crd && tmp->type == 0)
			exit(write(1, "xml error in lights: no crd\n", 28));
		if (!tmp->vec && tmp->type == 1)
			exit(write(1, "xml error in lights: no vec\n", 28));
		if (tmp->type != 1 && tmp->type != 0)
			exit(write(1, "xml error in lights: wrong type\n", 32));
		tmp = tmp->next;
	}
}

void			check_lights(t_light *light_lst)
{
	t_light	*cpy_lst;
	t_light	*cpy_check;

	check_lights_sub(light_lst);
	cpy_lst = light_lst;
	while (cpy_lst)
	{
		cpy_check = light_lst;
		while (cpy_check)
		{
			if (cpy_check != cpy_lst && cpy_check->id == cpy_lst->id)
				exit(write(1, "xml error in lights: identical id\n", 34));
			cpy_check = cpy_check->next;
		}
		cpy_lst = cpy_lst->next;
	}
}

void			check_materials(t_mat *mat_lst)
{
	t_mat	*cpy_lst;
	t_mat	*cpy_check;

	if (!mat_lst)
		exit(write(1, "xml error in materials: no materials\n", 36));
	cpy_lst = mat_lst;
	while (cpy_lst)
	{
		cpy_check = mat_lst;
		while (cpy_check)
		{
			if (cpy_check != cpy_lst && cpy_check->id == cpy_lst->id)
				exit(write(1, "xml error in materials: identical id\n", 37));
			cpy_check = cpy_check->next;
		}
		cpy_lst = cpy_lst->next;
	}
}

void			check_parameters(t_env *e)
{
	if (!e->width || !e->height)
		exit(write(1, "xml error in parameters: resolution\n", 36));
	if (e->width < 0 || e->height < 0)
		exit(write(1, "xml error in parameters: resolution too low\n", 44));
	if (e->width > 2000 || e->height > 2000)
		exit(write(1, "xml error in parameters: resolution too high\n", 45));
	if (!e->ambient || e->ambient < 0 || e->ambient > 1)
		exit(write(1, "xml error in parameters: ambient\n", 33));
	if (!e->background)
		exit(write(1, "xml error in parameters: background\n", 36));
	if (!e->cam)
		exit(write(1, "xml error in parameters: no camera\n", 35));
	if (!e->cam->crd)
		exit(write(1, "xml error in parameters: camera crd\n", 36));
}

void			check_parsing(t_env *e)
{
	xml_check_img(e);
	xml_check_tex_id(e);
	xml_check_tex_lst_type(e);
	check_materials(e->mat_lst);
	xml_check_obj_id(e);
	xml_check_obj_lst_type(e);
	xml_check_obj_norm_type(e);
	check_lights(e->light_lst);
}
