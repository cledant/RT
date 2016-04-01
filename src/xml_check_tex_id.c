/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_check_tex_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 13:01:39 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 16:36:38 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			xml_error_texture(int where, int type, int value)
{
	if (where == 1)
		ft_putendl("XML ERROR IN TEXTURE");
	else if (where == 2)
		ft_putendl("XML ERROR IN OBJECT");
	if (type == 1)
		ft_putstr("	Material ID = ");
	else if (type == 2)
		ft_putstr("	Image ID = ");
	else if (type == 3)
		ft_putstr("	Texture type = ");
	else if (type == 4)
		ft_putstr("	Object type = ");
	else if (type == 5)
		ft_putstr("	Texture ID = ");
	else if (type == 6)
		ft_putstr("	Normal type = ");
	ft_putnbr(value);
	ft_putendl(" doesn't exist");
	exit(0);
}

static void		tex_error(t_tex *cpy_lst)
{
	ft_putendl("XML ERROR IN TEXTURE");
	ft_putstr("	TEXTURE ID= ");
	ft_putnbr(cpy_lst->id);
	ft_putendl("");
	ft_putendl("	Duplicated ID");
	exit(0);
}

void			xml_check_tex_lst_type(t_env *e)
{
	t_tex	*cpy_lst;

	cpy_lst = e->tex_lst;
	while (cpy_lst != NULL)
	{
		xml_check_texture_type(cpy_lst->type);
		cpy_lst = cpy_lst->next;
	}
}

void			xml_check_tex_id(t_env *e)
{
	t_tex	*cpy_lst;
	t_tex	*cpy_check;

	cpy_lst = e->tex_lst;
	while (cpy_lst != NULL)
	{
		cpy_check = e->tex_lst;
		while (cpy_check != NULL)
		{
			if (cpy_check != cpy_lst && cpy_check->id == cpy_lst->id)
				tex_error(cpy_lst);
			cpy_check = cpy_check->next;
		}
		cpy_lst = cpy_lst->next;
	}
}
