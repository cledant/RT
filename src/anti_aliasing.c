/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 13:57:55 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/30 14:01:22 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			color_cmp(t_color *col1, t_color *col2)
{
	double d1;

	d1 = pow((col2->r - col1->r), 2) + pow((col2->g - col1->g), 2) + \
		pow((col2->b - col1->b), 2);
	if (d1 != 0)
		return (0);
	return (1);
}

t_color		*get_color_aa(t_ray *cam_ray, t_env *e, double x, double y)
{
	t_hit_pt	*hit_pt;
	t_color		*color;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	calc_cam_ray(x, y, cam_ray, e);
	e->nb_refle = 0;
	hit_pt = get_color(cam_ray, e);
	color->r = hit_pt->color->r;
	color->g = hit_pt->color->g;
	color->b = hit_pt->color->b;
	free_aa_hit_pt(hit_pt);
	return (color);
}

t_color		*add_color_2(t_ray *cam_ray, t_env *e, double x, double y)
{
	t_color	*color;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	color_init_null(color);
	add_color(color, get_color_aa(cam_ray, e, x + 0.5, y), 1);
	add_color(color, get_color_aa(cam_ray, e, x, y + 0.5), 1);
	add_color(color, get_color_aa(cam_ray, e, x + 0.5, y + 0.5), 1);
	add_color(color, get_color_aa(cam_ray, e, x + 1, y + 0.5), 1);
	add_color(color, get_color_aa(cam_ray, e, x + 0.5, y + 1), 1);
	return (color);
}

t_color		*anti_aliasing(double x, double y, t_ray *cam_ray, t_env *e)
{
	t_color *color;
	t_color *col_2;
	t_color *tmp[3];
	int		equal;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	color_init_null(color);
	add_color(color, get_color_aa(cam_ray, e, x, y), 1);
	tmp[0] = get_color_aa(cam_ray, e, x + 1, y + 1);
	equal = color_cmp(color, tmp[0]);
	add_color(color, tmp[0], 0);
	tmp[1] = get_color_aa(cam_ray, e, x + 1, y);
	equal = color_cmp(tmp[0], tmp[1]);
	add_color(color, tmp[1], 0);
	tmp[2] = get_color_aa(cam_ray, e, x, y + 1);
	equal = color_cmp(tmp[1], tmp[2]);
	add_color(color, tmp[2], 1);
	free(tmp[0]);
	free(tmp[1]);
	if (equal == 1)
		return (average_color(color, 4));
	col_2 = add_color_2(cam_ray, e, x, y);
	add_color(color, col_2, 1);
	return (average_color(color, 9));
}
