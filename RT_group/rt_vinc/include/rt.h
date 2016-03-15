/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 11:20:29 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <float.h>
# include <X11/X.h>
# include <math.h>

# include <stdio.h>////

# include "libft.h"
# include "mlx.h"

# define FOV_2 35
# define WIDTH 1280
# define HEIGHT 720
# define AMBIANT 0.33
# define LIGHT_INT 0xFF
# define SPECULAR_POW 16
# define light_LIGHT_INT 0x155
# define light_LIGHT_POW 4096
# define EPSILON 0.001
# define PI2 6.283185307179587
# define RADIAN 0.01745329251994329
# define INVALID "Invalid file"
# define GNL "get_next_line()"
# define MALLOC "malloc()"
# define CLOSE "close()"
# define PROG "rt"
# define CAM "cam"
# define CONE 1
# define TORUS 2
# define PLANE 3
# define SPHERE 4
# define CYLINDER 5
# define ELLIPSOID 6
# define PARABOLOID 7
# define HYPERBOLOID 8
# define MOBIUS_STRIP 9
# define HYPERBOLIC 10
# define ELLIPTIC 11
# define SHEET2 "two sheets"
# define SHEET1 "one sheet"
# define PX "px = "
# define PY "py = "
# define PZ "pz = "
# define RX "rx = "
# define RY "ry = "
# define RZ "rz = "
# define RT "R = "
# define R "r = "
# define A "a = "
# define B "b = "
# define C "c = "
# define HEX "0x"
# define NB_IT 5

/*
typedef struct		s_vec
{
	float			px;
	float			py;
	float			pz;
	float			x;
	float			y;
	float			z;
	float			pow2_x;
	float			pow2_y;
	float			pow2_z;
}									t_vec;
*/
typedef struct		s_vec
{
	float						x;
	float						y;
	float						z;
	float						pow2_x;
	float						pow2_y;
	float						pow2_z;
}									t_vec;

typedef struct		s_crd
{
	float						x;
	float						y;
	float						z;
}									t_crd;

typedef struct		s_ray
{
	t_crd						*crd;
	t_vec						*vec;
}									t_ray;

typedef struct		s_light
{
	t_crd						*crd;
	struct s_light	*next;
}									t_light;

typedef	struct		s_color
{
	int							r;
	int							g;
	int							b;
}									t_color;

typedef struct		s_mat
{
	t_color					*color;
	int							spec;
	int							id;
	float						refl;
}									t_mat;

typedef struct		s_obj
{
	int				type;
	int				id;
	//int				nbr;
	// int				red;
	// int				green;
	// int				blue;
	t_color		*color;
	t_mat			*mat;
	int				sign;
	// float			px;
	// float			py;
	// float			pz;
	t_crd			*crd;
	float			rx[3];
	float			ry[3];
	float			rz[3];
	float			r;
	float			tan_r;
	float			tan2_r;
	float			pow2_r;
	float			a;
	float			b;
	float			c;
	float			d;
	float			pow2_a;
	float			pow2_b;
	float			pow2_c;
	float			pow2_d;
	float			rt;
	float			pow2_rt;
	struct s_obj	*next;
}								t_obj;

typedef struct		s_cam
{
	// float			px;
	// float			py;
	// float			pz;
	t_crd			*crd;
	float			rx[3];
	float			ry[3];
	float			rz[3];
	float			pow2_px;
	float			pow2_py;
	float			pow2_pz;
	float			pow2_x[WIDTH][HEIGHT];
	float			pow2_y[WIDTH][HEIGHT];
	float			pow2_z[WIDTH][HEIGHT];
	float			x[WIDTH][HEIGHT];
	float			y[WIDTH][HEIGHT];
	float			z[WIDTH][HEIGHT];
}									t_cam;

typedef struct		s_env
{
	// float			depth;
	// int				width_2;
	// int				height_2;
	int				endian;
	int				size_l;
	int				bpp;
	int				fd;
	int				gnl;
	int				line_nbr;
	int				light_nbr;
	int				obj_nbr;
	int				nb_refle;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	char			*name;
	char			*line;
	t_ray			*ray;
	t_ray			*ray_cur;
	t_cam			*cam;
	t_obj			*obj_lst;
	t_obj			*obj_cur;
	t_light		*light_lst;
	t_light		*light_cur;
}									t_env;

int					ft_end_with_oid(int type);
int					ft_is_object(int type);
int					ft_is_object_char(char *str);
int					ft_inc_gnl(t_env *env);
int					ft_perror(char *msg, t_env *env);
int					ft_put_error(char *name, char *msg, t_env *env);
int					ft_free_env(t_env *env);
void				ft_init_env(t_env *env);
void				ft_make_obj(t_env *env);
void				ft_read_file(t_env *env);
void				ft_init_vector(t_cam *cam);
void				ft_set_nbr(int i, char *str, float *nbr, t_env *env);
void				ft_set_hex(t_obj *obj, t_env *env);
void				ft_draw(t_env *env);
void				ft_angle_cos_sin(float angle, float angle_cos_sin[3]);
void				ft_rotation_matrix(float *a, float *o, float an[3], int n);
void				ft_vector_rotation(float v[3], t_crd *crd, t_obj *ob, int n);
void				ft_vector_equation(t_obj *obj);
void				ft_set_v0(float *v0, t_vec *vec);
void				ft_set_pt0(float *pt0, t_obj *obj, t_crd *crd);
void				ft_rot_v0_pt0(float *v, float *p, t_obj *obj, t_crd *crd);
float				*ft_rot_pt1(float *pt1, t_obj *obj);
float				*ft_quadratic_equation(float a, float b, float c);
float				*ft_plane(t_obj *obj, t_ray *ray);
float				*ft_sphere(t_obj *obj, t_ray *ray);
float				*ft_cylinder(t_obj *obj, t_ray *ray);
float				*ft_cone(t_obj *obj, t_ray *ray);
float				*ft_tore(t_obj *obj, t_ray *ray);
float				*ft_paraboloid(t_obj *obj, t_ray *ray);
float				*ft_hyperboloid(t_obj *obj, t_ray *ray);
float				*ft_ellipsoid(t_obj *obj, t_ray *ray);
float				*ft_mobius_strip(t_obj *obj, t_ray *ray);
float				*ft_ray_collision(t_obj *obj, t_ray *ray);
int					ft_nearest_point(float pt[4], float *pt1, t_crd *crd);
void				ft_lux_tracing(int *color, float *pt, t_env *env);
void				ft_normal_direction(float *n, t_vec *vec);
void				ft_normal2(float *n, t_env *env);
void				ft_normal(float *v, t_env *env);
void				ft_check_color(int	*color);
void				ft_light_tracing(int *color, t_env *env);

#endif
