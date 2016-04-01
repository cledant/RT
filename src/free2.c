/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:53:52 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 17:08:08 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_ray(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->vec)
		free(ray->vec);
	if (ray->crd)
		free(ray->crd);
	free(ray);
}

t_interval	*interval_null(t_interval *i)
{
	free_interval(i);
	return (NULL);
}

void		free_tmp_ray(t_ray *ray)
{
	if (!ray)
		seg_fault();
	if (ray->vec)
		free(ray->vec);
	if (ray->crd)
		free(ray->crd);
	ray->vec = NULL;
	ray->crd = NULL;
}

int			free_tmp_interval(t_interval *i, t_ray *ray)
{
	free_interval(i);
	free_tmp_ray(ray);
	return (1);
}

void		free_transparency(t_hit_pt *hit_pt, t_ray *ray, t_env *env)
{
	free_hit_pt(hit_pt, env);
	free_tmp_ray(ray);
}
