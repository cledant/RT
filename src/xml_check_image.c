/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminettedemerde.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:37:08 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:37:28 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	image_error(t_img *cpy_lst, int error)
{
	ft_putendl("XML ERROR IN IMAGES");
	ft_putstr("	IMAGE ID= ");
	ft_putnbr(cpy_lst->id);
	ft_putendl("");
	if (error == 1)
		ft_putendl("	Images couldn't be loaded");
	else if (error == 2)
		ft_putendl("	Images data couldn't be loaded");
	else if (error == 3)
		ft_putendl("	Duplicated ID");
	exit(0);
}

static void	xml_check_img_id(t_img *lst)
{
	t_img	*cpy_lst;
	t_img	*cpy_check;

	cpy_lst = lst;
	while (cpy_lst != NULL)
	{
		cpy_check = lst;
		while (cpy_check != NULL)
		{
			if (cpy_check != cpy_lst && cpy_check->id == cpy_lst->id)
				image_error(cpy_lst, 3);
			cpy_check = cpy_check->next;
		}
		cpy_lst = cpy_lst->next;
	}
}

void		xml_check_img(t_env *e)
{
	t_img	*cpy_lst;

	cpy_lst = e->img_lst;
	while (cpy_lst != NULL)
	{
		if (cpy_lst->img == NULL)
			image_error(cpy_lst, 1);
		if (cpy_lst->data == NULL)
			image_error(cpy_lst, 2);
		cpy_lst = cpy_lst->next;
	}
	xml_check_img_id(e->img_lst);
}
