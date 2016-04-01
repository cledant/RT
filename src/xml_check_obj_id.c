/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putaindemerde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 16:26:27 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 19:48:39 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		tex_error(t_obj *cpy_lst)
{
	ft_putendl("XML ERROR IN OBJECT");
	ft_putstr("	OBJECT ID= ");
	ft_putnbr(cpy_lst->id);
	ft_putendl("");
	ft_putendl("	Duplicated ID");
	exit(0);
}

void			xml_check_obj_lst_type(t_env *e)
{
	t_obj	*cpy_lst;

	cpy_lst = e->obj_lst;
	while (cpy_lst != NULL)
	{
		xml_check_obj_type(cpy_lst->type);
		cpy_lst = cpy_lst->next;
	}
}

void			xml_check_obj_id(t_env *e)
{
	t_obj	*cpy_lst;
	t_obj	*cpy_check;

	cpy_lst = e->obj_lst;
	while (cpy_lst != NULL)
	{
		cpy_check = e->obj_lst;
		while (cpy_check != NULL)
		{
			if (cpy_check != cpy_lst && cpy_check->id == cpy_lst->id)
				tex_error(cpy_lst);
			cpy_check = cpy_check->next;
		}
		cpy_lst = cpy_lst->next;
	}
}

void			xml_check_obj_norm_type(t_env *e)
{
	t_obj	*cpy_lst;

	cpy_lst = e->obj_lst;
	while (cpy_lst != NULL)
	{
		if (cpy_lst->norm_type < 0 || cpy_lst->norm_type > 4)
			xml_error_texture(2, 6, cpy_lst->norm_type);
		if (cpy_lst->norm_type == 4 && cpy_lst->bump_img == NULL)
		{
			ft_putendl("XML ERROR IN OBJECT");
			ft_putendl("	Please set an image ID if using normal type = 4");
			exit(0);
		}
		cpy_lst = cpy_lst->next;
	}
}
