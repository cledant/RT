/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:36:58 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:34:15 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_init_env0(t_env *env)
{
	int	l;

	if (!(env->ray_cur = (t_ray *)malloc(sizeof(t_ray))))
		exit(ft_perror(MALLOC, env));
	if (!(env->ray_cur->crd = (t_crd *)malloc(sizeof(t_crd))))
		exit(ft_perror(MALLOC, env));
	if (!(env->ray_cur->vec = (t_vec *)malloc(sizeof(t_vec))))
		exit(ft_perror(MALLOC, env));
	if (!(env->ray = (t_ray *)malloc(sizeof(t_ray))))
		exit(ft_perror(MALLOC, env));
	if (!(env->ray->crd = (t_crd *)malloc(sizeof(t_crd))))
		exit(ft_perror(MALLOC, env));
	if (!(env->ray->vec = (t_vec *)malloc(sizeof(t_vec))))
		exit(ft_perror(MALLOC, env));
	if (!(env->cam = (t_cam *)malloc(sizeof(t_cam))))
		exit(ft_perror(MALLOC, env));
	if (!(env->cam->crd = (t_crd *)malloc(sizeof(t_crd))))
		exit(ft_perror(MALLOC, env));
	if (!(env->mlx = mlx_init()))
		exit(ft_perror("mlx_init()", env));
	if (!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, PROG)))
		exit(ft_perror("mlx_new_window()", env));
	if (!(env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		exit(ft_perror("mlx_new_image()", env));
	l = WIDTH * 4;
	if (!(env->addr = mlx_get_data_addr(env->img, &env->bpp, &l, &env->endian)))
		exit(ft_perror("mlx_get_data_addr()", env));
}

void		ft_init_env(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->addr = NULL;
	env->line = NULL;
	env->obj_lst = NULL;
	env->cam = NULL;
	env->ray = NULL;
	env->ray_cur = NULL;
	env->light_lst = NULL;
	env->light_nbr = 0;
	env->line_nbr = 0;
	env->obj_nbr = 0;
	env->bpp = 4 * CHAR_BIT;
	env->endian = ft_endian();
	return (ft_init_env0(env));
}

void		ft_init_vector(t_cam *cam)
{
	int		i;
	int		j;
	int		width_2;
	int		height_2;
	float	depth;

	width_2 = WIDTH / 2;
	height_2 = HEIGHT / 2;
	depth = height_2 / tan(FOV_2);
	i = -1;
	while ((i += 1) < WIDTH)
	{
		j = -1;
		while ((j += 1) < HEIGHT)
		{
			cam->x[i][j] = depth;
			cam->y[i][j] = width_2 - i;
			cam->z[i][j] = height_2 - j;
			ft_rotation_matrix(&cam->x[i][j], &cam->y[i][j], cam->rz, 0);
			ft_rotation_matrix(&cam->y[i][j], &cam->z[i][j], cam->rx, 0);
			ft_rotation_matrix(&cam->z[i][j], &cam->x[i][j], cam->ry, 0);
			cam->pow2_x[i][j] = powf(cam->x[i][j], 2);
			cam->pow2_y[i][j] = powf(cam->y[i][j], 2);
			cam->pow2_z[i][j] = powf(cam->z[i][j], 2);
		}
	}
}
