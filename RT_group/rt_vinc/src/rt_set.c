/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:14:50 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 11:19:22 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_inc_gnl(t_env *env)
{
	env->line_nbr += 1;
	return ((env->gnl = get_next_line(env->fd, &env->line)));
}

void	ft_angle_cos_sin(float angle, float angle_cos_sin[3])
{
	if (!angle_cos_sin)
		return ;
	angle_cos_sin[0] = angle;
	angle_cos_sin[1] = cos(angle);
	angle_cos_sin[2] = sin(angle);
}

void	ft_set_nbr(int i, char *str, float *nbr, t_env *env)
{
	int		l;

	l = ft_strlen(str);
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	if (ft_strncmp(env->line, str, l))
		exit(ft_put_error(env->name, INVALID, env));
	nbr[0] = ft_atoi(&env->line[l]);
	if (i)
		nbr[0] *= RADIAN;
	if (i > 1)
		ft_angle_cos_sin(nbr[0], nbr);
	ft_inc_gnl(env);
}

void	ft_set_hex(t_obj *obj, t_env *env)
{
	int		l[2];
	char	s[3];

	l[0] = ft_strlen(HEX);
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	if (ft_strncmp(env->line, HEX, l[0]))
		exit(ft_put_error(env->name, INVALID, env));
	l[1] = 0;
	while (ft_ishexa(env->line[l[0] + l[1]]))
		l[1]++;
	if (l[1] != 6)
		exit(ft_put_error(env->name, INVALID, env));
	s[2] = '\0';
	obj->color->r = ft_xtoi(ft_memcpy(s, &env->line[l[0]], 2));
	obj->color->g = ft_xtoi(ft_memcpy(s, &env->line[l[0] + 2], 2));
	obj->color->b = ft_xtoi(ft_memcpy(s, &env->line[l[0] + 4], 2));
	ft_inc_gnl(env);
}
