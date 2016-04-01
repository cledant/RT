/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:53:52 by vlize             #+#    #+#             */
/*   Updated: 2016/03/31 13:32:46 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_obj_lst(t_env *e)
{
	t_obj	*prev;

	while (e->obj_lst != NULL)
	{
		prev = e->obj_lst;
		e->obj_lst = e->obj_lst->next;
		free(prev->crd);
		free(prev);
	}
}

static void	free_csg_lst(t_env *e)
{
	t_csg	*prev;

	while (e->csg_lst != NULL)
	{
		prev = e->csg_lst;
		e->csg_lst = e->csg_lst->next;
		free(prev->crd);
		free(prev);
	}
	free_obj_lst(e);
}

static void	free_light_lst(t_env *e)
{
	t_light	*prev;

	while (e->light_lst != NULL)
	{
		prev = e->light_lst;
		e->light_lst = e->light_lst->next;
		if (prev->type == 1)
			free(prev->vec);
		else
			free(prev->crd);
		free(prev);
	}
	free_csg_lst(e);
}

static void	free_mat_lst(t_env *e)
{
	t_mat	*prev;

	while (e->mat_lst != NULL)
	{
		prev = e->mat_lst;
		e->mat_lst = e->mat_lst->next;
		free(prev->color);
		free(prev);
	}
	free_light_lst(e);
}

void		free_tex_lst(t_env *e)
{
	t_tex	*prev;

	while (e->tex_lst != NULL)
	{
		prev = e->tex_lst;
		e->tex_lst = e->tex_lst->next;
		free(prev);
	}
	free_mat_lst(e);
}
