/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:36:58 by vlize             #+#    #+#             */
/*   Updated: 2016/03/31 14:44:52 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->width + 200, e->height, e->scene_name);
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	e->img_cpy = mlx_new_image(e->mlx, e->width, e->height);
	e->addr = mlx_get_data_addr(e->img, &e->bit, &e->size, &e->end);
	e->addr_cpy = mlx_get_data_addr(e->img_cpy, &e->bit, &e->size, &e->end);
	e->img_load = mlx_new_image(e->mlx, 199, 20);
	e->addr_load = mlx_get_data_addr(e->img_load, &e->bit_load,
			&e->size_load, &e->end_load);
	e->img_aa = mlx_new_image(e->mlx, e->width, e->height);
	e->addr_aa = mlx_get_data_addr(e->img_aa, &e->bit, &e->size, &e->end);
}

void		init_rot(t_obj **hit_obj)
{
	(*hit_obj)->rz[0] = 0;
	(*hit_obj)->rz[1] = 1;
	(*hit_obj)->rz[2] = 0;
	(*hit_obj)->ry[0] = 0;
	(*hit_obj)->ry[1] = 1;
	(*hit_obj)->ry[2] = 0;
	(*hit_obj)->rx[0] = 0;
	(*hit_obj)->rx[1] = 1;
	(*hit_obj)->rx[2] = 0;
}

int			nb_lights(t_env *e)
{
	t_light	*tmp_light;
	int		nb;

	nb = 0;
	tmp_light = e->light_lst;
	while (tmp_light)
	{
		nb++;
		tmp_light = tmp_light->next;
	}
	return (nb);
}

t_hit_pt	*hit_pt_init(t_ray *ray)
{
	t_hit_pt	*hit_pt;

	if (!(hit_pt = (t_hit_pt *)malloc(sizeof(t_hit_pt))))
		malloc_error(0);
	if (!(hit_pt->normal = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error(0);
	if (!(hit_pt->root_ray = (t_ray *)malloc(sizeof(t_ray))))
		malloc_error(0);
	if (!(hit_pt->root_ray->crd = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error(0);
	if (!(hit_pt->root_ray->vec = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error(0);
	hit_pt->root_ray->crd->x = ray->crd->x;
	hit_pt->root_ray->crd->y = ray->crd->y;
	hit_pt->root_ray->crd->z = ray->crd->z;
	hit_pt->root_ray->vec->x = ray->vec->x;
	hit_pt->root_ray->vec->y = ray->vec->y;
	hit_pt->root_ray->vec->z = ray->vec->z;
	return (hit_pt);
}

void		init(char *arg, t_env *env)
{
	int		fd;
	t_menu	*menu;

	menu = NULL;
	if ((fd = open(arg, O_RDONLY)) < 0)
		exit(write(1, "scene name error\n", 17));
	parsing(fd, env);
	check_parsing(env);
	env->nb_rays = 0;
	env->aa = 0;
	env->nb_lights = nb_lights(env);
	if (!(menu = (t_menu *)malloc(sizeof(t_menu))))
		malloc_error(0);
	menu->filter_button = 0;
	menu->aa_button = 0;
	menu->selected = 0;
	menu->ind_elem = 0;
	if (!(menu->data = (double**)malloc(sizeof(double*) * 6)))
		malloc_error(0);
	if (!(menu->obj_name = (char*)malloc(sizeof(char) * 21)))
		malloc_error(0);
	env->menu = menu;
	get_elem(env);
	close(fd);
}
