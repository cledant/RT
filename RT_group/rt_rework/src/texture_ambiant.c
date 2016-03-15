/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_ambiant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 19:51:09 by cledant           #+#    #+#             */
/*   Updated: 2016/03/14 20:40:43 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_tex_color(t_color *color, char *addr, float coef)
{
	char	s[3];

	ft_bzero(s, 3);
	color->r = ft_xtoi(ft_memcpy(s, &addr[0], 2));
	color->g = ft_xtoi(ft_memcpy(s, &addr[2], 2));
	color->b = ft_xtoi(ft_memcpy(s, &addr[4], 2));
	color->r /= 255;
	color->g /= 255;
	color->b /= 255;
	color->r *= coef;
	color->g *= coef;
	color->b *= coef;
}

void			texture_ambiant(t_color *color, float coef, t_hit_pt *hit_pt,
					t_obj *obj)
{
	float		u;
	float		v;
	t_vector3	p;
	char		*addr;
	t_tex		*tex;

	tex = obj->mat->tex;
	p.x = hit_pt->crd->x - obj->crd->x;
	p.y = hit_pt->crd->y - obj->crd->y;
	p.z = hit_pt->crd->z - obj->crd->z;
/*	printf("TEST\n");
	printf("x = %f\n",  p.x);
	printf("y = %f\n",  p.y);
	printf("z = %f\n",  p.z);
	printf("W = %d\n",  tex->width);
	printf("H = %d\n",  tex->height);
*/	normalise(&p);
	u = 0.5 + atan2(p.z, p.y) / PI2;
	v = 0.5 - asin(p.y) / M_PI;
	addr = tex->data + (int)(u * tex->width) * 4 + (int)(v * tex->height) *
		tex->width * 4;
	get_tex_color(color, addr, coef);
}
