/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/14 20:05:07 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <float.h>
// # include <X11/X.h>
// #include "include/mlx.h"
# include <math.h>

# include <stdio.h>////

# include "libft.h"
# include "mlx.h"

# define EPSILON 0.001
# define FOV 0.4738147204
# define PI2 6.283185307179587
# define RADIAN 0.01745329251994329
# define MAX_REFLE 5 ////

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4
# define TORUS 5
# define ELLIPSOID 6
# define PARABOLOID 7
# define HYPERBOLOID 8
# define HYPERBOLIC 10
# define ELLIPTIC 11

# define NB_IT 5

typedef struct		s_vector3
{
	float						x;
	float						y;
	float						z;
}									t_vector3;

typedef struct		s_ray
{
	t_vector3				*crd;
	t_vector3				*vec;
}									t_ray;

typedef	struct		s_color
{
	float						r;
	float						g;
	float						b;
}									t_color;

typedef struct		s_tex
{
	int				id;
	int				type;
	int				proc_type;
	void			*img;
	char			*data;
	int				width;
	int				height;
	struct s_tex	*next;
}					t_tex;

typedef struct		s_mat
{
	t_color					*color;
	t_tex					*tex;
	int							spec;
	int							id;
	int							refl;
	struct s_mat		*next;
}									t_mat;

typedef struct		s_light
{
	int							id;
	int							type;
	t_vector3				*crd;
	t_color					*color;
	struct s_light	*next;
}									t_light;

typedef struct		s_obj
{
	int						type;
	int						id;
	t_color				*color;
	t_mat					*mat;
	int						sign;
	t_vector3			*crd;
	float					rx[3];
	float					ry[3];
	float					rz[3];
	float					r;
	float					tan_r;
	float					tan2_r;
	float					pow2_r;
	float					a;
	float					b;
	float					c;
	float					d;
	float					pow2_a;
	float					pow2_b;
	float					pow2_c;
	float					pow2_d;
	float					rt;
	float					pow2_rt;
	struct s_obj	*next;
}								t_obj;

typedef struct		s_hit_pt
{
	t_vector3				*crd;
	t_vector3				*normal;
	t_ray						*root_ray;
	t_color					*color;
}									t_hit_pt;

typedef struct		s_cam
{
	t_vector3			*crd;
	float			rx[3];
	float			ry[3];
	float			rz[3];
}									t_cam;

typedef struct		s_env
{
	void						*mlx;
	void						*win;
	void						*img;
	char						*addr;
	int							bit;
	int							size;
	int							end;

	char						*scene_name;
	int							width;
	int							height;

	t_color					*background;
	float						ambient;
	int							aa;
	int							nb_refle;

	t_cam						*cam;
	t_obj						*obj_lst;
	t_light					*light_lst;
	t_mat						*mat_lst;
	t_tex						*tex_lst;
}									t_env;

//init.c
void 							init(char *arg, t_env *env);
void							init_mlx(t_env *e);

//parser.c
void   						parsing(int fd, t_env *e);

//parsing_func.c
int  							xml_cmp(char *str, char *ref);
void 							rec_cam(int fd, char *ret, t_env *e);
t_mat 						*rec_mat(char *str, t_mat *mat_lst);
int								rec_int_value(char *str);
float						 	rec_float_value(char *str);
t_color 					*rec_color(char *str);
t_vector3 				*rec_vec(char *str);
char 							*rec_name(char *str);
void  						rec_rot(char *str, t_obj *obj);
t_tex						*rec_texture(char *str, t_tex *lst_tex);
int							rec_texture_type(char *ret);
void						rec_texture_file(t_tex *tex, char *ret, void *mlx);
void						rec_texture_proc(t_tex *tex, char *ret);

//create_list.c
t_mat 						*add_mat(int fd, char *ret, t_mat *mat, t_tex *lst_tex);
t_light					 	*add_light(int fd, char *ret, t_light *light);
t_obj 						*add_obj(int fd, char *ret, t_obj *obj, t_mat *mat);
t_tex 						*add_tex(int fd, char *ret, t_tex *tex, void *mlx);

//debug.c
void 							debug(t_env *e);

//error.c
void 							malloc_error();
void							arg_error();

//raytracer.c
void 							cap_color(t_color *color);
void 							raytracer(t_env *e);

//general_func.c
void							normalise(t_vector3 *vec);

//get_color.c
t_hit_pt 					*get_color(t_ray *ray, t_env *e);

//find_intersect.c
t_vector3 				*find_intersect(t_ray *ray, t_obj *obj_lst, t_obj **hit_obj);
t_vector3					*ray_collision(t_obj *obj, t_ray *ray);

//object_1.c
t_vector3 *plane(t_obj *obj, t_ray *ray);
t_vector3 *sphere(t_obj *obj, t_ray *ray);
t_vector3 *cylinder(t_obj *obj, t_ray *ray);
t_vector3 *cone(t_obj *obj, t_ray *ray);

//object_2.c
t_vector3 *paraboloid(t_obj *obj, t_ray *ray);
t_vector3 *hyperboloid(t_obj *obj, t_ray *ray);
t_vector3 *ellipsoid(t_obj *obj, t_ray *ray);

//rotation.c
void	rotation_matrix(float *absc, float *ord, float angle[3], int neg);
void	vector_rotation(t_vector3 *vec, t_obj *obj, int neg);
void	vector_equation(t_obj *obj);

//sub_function.c
float	*find_det(float a, float b, float c);
void	vec_cpy(t_vector3 *dst, t_vector3 *src);
void	set_vec(t_vector3 *vec, t_obj *obj, t_vector3 *crd);
// void	rot_v0_pt0(float *v0, float *pt0, t_obj *obj, t_vector3 *crd);
t_vector3	*rot_pt1(t_vector3 *pt1, t_obj *obj);
// void	normal_direction(float *n, t_vector3 *vec);
t_vector3	*refle_vec(t_vector3 *normal, t_vector3 *src_vec);

//normal.c
void	get_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt);

//calc_color.c
t_color   *calc_color(t_hit_pt *hit_pt, t_obj *hit_obj, t_env *e);

//reflection.c
void 			reflection(t_env *env, t_obj *hit_obj, t_hit_pt *hit_pt);

//texture_ambiant.c
void			texture_ambiant(t_color *color, float coef, t_hit_pt *hit_pt,
					t_obj *obj);

#endif
