/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:08:46 by mbragard          #+#    #+#             */
/*   Updated: 2016/03/30 17:12:59 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_aa_hit_pt(t_hit_pt *hit_pt)
{
	if (hit_pt)
	{
		if (hit_pt->root_ray->vec)
			free(hit_pt->root_ray->vec);
		if (hit_pt->root_ray->crd)
			free(hit_pt->root_ray->crd);
		free(hit_pt->root_ray);
		free(hit_pt->crd);
		free(hit_pt->normal);
		if (hit_pt->color)
			free(hit_pt->color);
		free(hit_pt);
	}
}

void	free_hit_pt(t_hit_pt *hit_pt, t_env *e)
{
	if (hit_pt)
	{
		if (e->aa == 0)
		{
			if (hit_pt->root_ray->vec)
				free(hit_pt->root_ray->vec);
			if (hit_pt->root_ray->crd)
				free(hit_pt->root_ray->crd);
			free(hit_pt->root_ray);
			free(hit_pt->crd);
			free(hit_pt->normal);
		}
		if (hit_pt->color)
			free(hit_pt->color);
		free(hit_pt);
	}
}

int		free_interval(t_interval *i)
{
	t_interval	*tmp;

	while (i)
	{
		tmp = i->next;
		free(i);
		i = tmp;
	}
	return (1);
}

void	free_tree(t_node *tree)
{
	t_node	*tmp;

	if (!tree)
		return ;
	if (tree->fork1)
		free_tree(tree->fork1);
	tmp = tree->fork2;
	free(tree);
	return (free_tree(tmp));
}

void	free_csg(t_csg *csg)
{
	if (csg->crd)
		free(csg->crd);
	if (csg->tree)
		free_tree(csg->tree);
	free(csg);
}
