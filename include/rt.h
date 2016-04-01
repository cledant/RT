/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/31 16:59:53 by tpierron         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"

# define EPSILON 0.001
# define FOV 0.4738147204
# define PI2 6.283185307179587
# define RADIAN 0.01745329251994329
# define MAX_REFLE 5

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4
# define ELLIPSOID 5
# define PARABOLOID 6
# define HYPERBOLOID 7

# define NB_IT 5

# define UNION 1
# define DIFFERENCE 2
# define INTERSECTION 3

typedef struct					s_vector3
{
	double						x;
	double						y;
	double						z;
}								t_vector3;

typedef struct					s_ray
{
	t_vector3					*crd;
	t_vector3					*vec;
	double						intensity;
	double						dist[2];
}								t_ray;

typedef	struct					s_color
{
	double						r;
	double						g;
	double						b;
}								t_color;

typedef struct					s_img
{
	int							id;
	void						*img;
	void						*data;
	int							img_width;
	int							img_height;
	struct s_img				*next;
}								t_img;

typedef struct					s_mat
{
	t_color						*color;
	int							spec;
	int							id;
	int							refl;
	int							trans;
	double						ind_trans;
	struct s_mat				*next;
}								t_mat;

typedef struct					s_tex
{
	int							id;
	int							type;
	t_mat						*mat_1;
	t_mat						*mat_2;
	t_mat						*mat_img;
	t_img						*img;
	float						size;
	struct s_tex				*next;
	int							grad_r;
	int							grad_g;
	int							grad_b;
	float						freq;
	float						octa;
}								t_tex;

typedef struct					s_light
{
	int							id;
	int							type;
	t_vector3					*crd;
	t_vector3					*vec;
	int							intensity;
	struct s_light				*next;
}								t_light;

typedef struct					s_obj
{
	int							type;
	int							id;
	t_tex						*tex;
	t_mat						*mat;
	t_vector3					*crd;
	t_img						*bump_img;
	float						norm_freq;
	int							norm_type;
	int							sign;
	double						rx[3];
	double						ry[3];
	double						rz[3];
	double						r;
	double						r2;
	double						tan_r;
	double						tan2_r;
	double						a;
	double						b;
	double						c;
	double						a2;
	double						b2;
	double						c2;
	double						size_x;
	double						size_y;
	double						size_z;
	double						tr_x;
	double						tr_y;
	double						tr_z;
	struct s_obj				*next;
}								t_obj;

typedef struct					s_interval
{
	double						min;
	double						max;
	t_obj						*obj_max;
	t_obj						*obj_min;
	struct s_interval			*next;
}								t_interval;

typedef struct					s_node
{
	int							type;
	t_obj						*obj;
	struct s_node				*fork1;
	struct s_node				*fork2;
}								t_node;

typedef struct					s_csg
{
	int							id;
	double						scale;
	t_vector3					*crd;
	double						rx[3];
	double						ry[3];
	double						rz[3];
	t_node						*tree;
	struct s_csg				*next;
}								t_csg;

typedef struct					s_hit_pt
{
	int							hit_obj_id;
	t_vector3					*crd;
	t_vector3					*normal;
	t_ray						*root_ray;
	double						light_sum;
	t_color						*color;
	double						diff_rate;
}								t_hit_pt;

typedef struct					s_cam
{
	t_vector3					*crd;
	double						rx[3];
	double						ry[3];
	double						rz[3];
}								t_cam;

typedef struct					s_menu
{
	int							filter_button;
	int							aa_button;
	int							ind_elem;
	char						*text;
	double						**data;
	char						*obj_name;
	int							selected;
}								t_menu;

typedef struct					s_env
{
	void						*mlx;
	void						*win;

	void						*img;
	char						*addr;
	int							bit;
	int							size;
	int							end;

	void						*img_load;
	char						*addr_load;
	int							bit_load;
	int							size_load;
	int							end_load;

	void						*img_aa;
	char						*addr_aa;

	void						*img_cpy;
	char						*addr_cpy;

	char						*scene_name;
	int							width;
	int							height;

	double						light_dist[2];
	double						trans_tmp;

	t_color						*background;
	double						ambient;
	int							aa;
	int							nb_refle;

	int							nb_lights;
	int							nb_rays;

	t_menu						*menu;
	t_cam						*cam;
	t_obj						*obj_lst;
	t_csg						*csg_lst;
	t_light						*light_lst;
	t_mat						*mat_lst;
	t_img						*img_lst;
	t_tex						*tex_lst;
}								t_env;

void							init(char *arg, t_env *env);
void							init_mlx(t_env *e);
t_hit_pt						*hit_pt_init(t_ray *ray);

void							parsing(int fd, t_env *e);

void							textures_init(int fd, char *ret, t_env *e);
void							images_init(int fd, char *ret, t_env *e);

void							rec_angle(double nbr, double *angle, int deg);
int								xml_cmp(char *str, char *ref);
void							rec_cam(int fd, char *ret, t_env *e);
t_mat							*rec_mat(char *str, t_mat *mat_lst);
int								rec_int_value(char *str);
t_color							*rec_color(char *str);
t_vector3						*rec_vec(char *str);
char							*rec_name(char *str);
void							rec_rot(char *str, t_obj *obj);
t_tex							*rec_texture(char *str, t_tex *lst_tex);
int								rec_texture_type(char *ret);
t_img							*rec_img_addr(char *str, t_img *lst_img, \
								int where);
void							rec_image_file(t_img **img, char *ret, \
								void *mlx);
t_mat							*rec_mat_addr(char *str, t_mat *lst_mat);
void							rec_coef(t_obj *obj, char *str);
int								rec_sign(char *str);
void							rec_rot_cam(char *str, t_cam *cam);

t_mat							*add_mat(int fd, char *ret, t_mat *mat);
t_light							*add_light(int fd, char *ret, t_light *light);
t_obj							*add_obj(int fd, char *ret, t_obj *obj, \
								t_env *env);
t_csg							*add_csg(int fd, char *ret, t_env *env);
t_tex							*add_tex(int fd, char *ret, t_tex *tex, \
								t_env *e);
t_img							*add_img(int fd, char *ret, t_img *img, \
								void *mlx);

void							debug(t_env *e);

void							malloc_error();
void							seg_fault();
void							arg_error();

void							calc_cam_ray(double x, double y, \
								t_ray *cam, t_env *e);
void							raytracer(t_env *e, char *addr);

void							save_image(char *img, t_env *e);
void							normalise(t_vector3 *vec);
int								quadratic_roots(double *deg, double *k);
void							normal_direction(t_vector3 *norm, \
								t_vector3 *vec);

t_hit_pt						*get_color(t_ray *ray, t_env *e);

t_vector3						*find_intersect(t_ray *ray, t_env *e, \
								t_obj **hit_obj);
void							make_csg_ray(t_ray *ray1, t_ray *ray2, \
								t_csg *csg);

int								ray_collision(t_obj *obj, t_ray *ray, \
								double *k);
int								smallest_k(t_obj *obj, t_ray *ray, double *k);

int								is_in_shadow(t_env *env, t_ray *light_ray, \
								t_color *color, t_light *light);

int								plane(t_obj *obj, t_ray *ray, double k[4]);
int								sphere(t_obj *obj, t_ray *ray, double k[4]);
int								cylinder(t_obj *obj, t_ray *ray, double k[4]);

int								cone(t_obj *obj, t_ray *ray, double k[4]);

int								paraboloid(t_obj *obj, t_ray *ray, double k[4]);
int								hyperboloid(t_obj *obj, t_ray *ray, \
								double k[4]);
int								ellipsoid(t_obj *obj, t_ray *ray, double k[4]);

void							rotation_matrix(double *absc, double *ord, \
								double angle[3], int neg);
void							vector_rotation(t_vector3 *vec, t_obj *obj, \
								int neg);
void							csg_rotation(t_vector3 *vec, t_csg *csg, \
								int neg);
void							init_rot(t_obj **hit_obj);

double							get_dist(t_vector3 *p1, t_vector3 *p2);
double							*find_det(double a, double b, double c);
void							vec_cpy(t_vector3 *dst, t_vector3 *src);
void							set_vec(t_vector3 *vec, t_vector3 *p1, \
								t_vector3 *p2);
void							seek_uv_plane(t_hit_pt *hit_pt, t_obj *obj, \
								double *x, double *y);
void							seek_uv_sph(t_hit_pt *hit_pt, \
								t_obj *obj, double *u, double *v);
void							seek_uv_cyl_cone(t_hit_pt *hit_pt, t_obj *obj, \
								double *u, double *v);
t_vector3						*rot_pt1(t_vector3 *pt1, t_obj *obj);
void							normal_direction(t_vector3 *norm, t_vector3 \
								*vec);
t_vector3						*refle_vec(t_vector3 *normal, t_vector3 \
								*src_vec);
t_vector3						*refre_vec(t_vector3 *normal, t_vector3 \
								*incident, double ind_prev, double ind_next);
void							seek_uv_plane_img(t_hit_pt *hit_pt, \
								t_obj *obj, double (*uv)[4]);
void							seek_uv_cyl_cone_img(t_hit_pt *hit_pt, \
								t_obj *obj, double (*uv)[4], int width);
void							put_color(t_env *e, char *img, int *v, \
								unsigned char *save);
void							small_malloc(t_ray *light_ray);

void							get_normal(t_vector3 *norm, t_obj *hit_obj, \
								t_vector3 *hit_pt);
void							check_normal(t_csg *csg_lst, t_vector3 \
								*normal, t_vector3 *ori, t_obj *hit_obj);
void							sin_change_normal(t_hit_pt *hit_pt, \
								t_obj *hit_obj);
void							perlin_change_normal(t_hit_pt *hit_pt, \
								t_obj *hit_obj);
float							get_img_norm(char *addr);
void							image_change_normal(t_hit_pt *hit_pt, \
								t_obj *hit_obj);
void							fuse_dot_change_normal(t_hit_pt *hit_pt, \
								t_obj *hit_obj);

t_color							*calc_color(t_hit_pt *hit_pt, t_obj \
								*hit_obj, t_env *e);
void							transparency(t_env *env, t_obj *hit_obj, \
								t_hit_pt *hit_pt);
void							reflection(t_env *env, t_obj *hit_obj, \
								t_hit_pt *hit_pt);
t_mat							*hit_material(t_hit_pt *hit_pt, t_obj *obj);
t_mat							*img_xy_plane(t_hit_pt *hit_pt, t_obj *obj);
void							black_and_white(t_env *e);
void							sepia(t_env *e);
t_color							*anti_aliasing(double x, double y, \
								t_ray *cam_ray, t_env *e);
void							free_hit_pt(t_hit_pt *hit_pt, t_env *e);
void							free_aa_hit_pt(t_hit_pt *hit_pt);
void							free_csg(t_csg *csg);
void							free_tree(t_node *tree);
int								free_interval(t_interval *i);
t_interval						*interval_null(t_interval *i);
void							free_tmp_ray(t_ray *ray);
int								free_tmp_interval(t_interval *i, t_ray *ray);
void							free_transparency(t_hit_pt *hit_pt, \
								t_ray *ray, t_env *env);
void							free_ray(t_ray *ray);
void							free_env(t_env *e);
void							free_tex_lst(t_env *e);
void							make_tmp_ray(t_ray *tmp_ray, t_vector3 *vec, \
								t_vector3 *crd, t_vector3 *ori);
t_interval						*new_interval(double *k, t_obj *obj);
t_node							*new_node(int type);
t_csg							*new_csg(int id);
t_vector3						*new_point(t_vector3 *pt, t_vector3 *vec, \
								t_vector3 *crd, double k);
t_obj							*ray_collision_csg(t_csg *csg, \
								t_ray *ray, double *k);
t_interval						*intersection_interval(t_interval *i1, \
								t_interval *i2);
t_interval						*difference_interval(t_interval *i1, \
								t_interval *i2);
t_interval						*union_interval(t_interval *i1, t_interval *i2);
t_interval						*get_interval(t_node *node, t_ray *ray);
double							perlin_noise(double x, double y, double p, \
								int n);
double							perlin_noise_3d(t_vector3 *vec, double p, \
								int n);
double							ft_noise_3d(int x, int y, int z);
void							print_menu(t_env *e);
void							print_loading(t_env *e);
int								center(char *text);
void							clear_menu(t_env *e);
int								*fill_params(int x, int y, int width, \
								int heigth);
int								mouse_press(int button, int x, int y, t_env *e);
int								ft_key_hook(int keycode, t_env *e);
void							get_cam(t_env *e);
void							find_light(t_env *e);
void							find_object(t_env *e, t_obj *obj_tmp, int i, \
								t_obj *previous);

void							selection(t_env *e, int y);
void							switch_obj(t_env *e, int ind);
char							get_char(int keycode);
void							print_modification(t_env *e, int y, \
								char *text, int color);
void							get_elem(t_env *e);

void							paraboloid_normal(t_vector3 *norm, t_obj \
								*hit_obj, t_vector3 *hit_pt);
void							cone_normal(t_vector3 *norm, t_obj *hit_obj,\
								t_vector3 *hit_pt);
void							cylinder_normal(t_vector3 *norm, t_obj \
								*hit_obj, t_vector3 *hit_pt);
void							sphere_normal(t_vector3 *norm, t_obj *hit_obj, \
								t_vector3 *hit_pt);
void							plane_normal(t_vector3 *norm, t_obj *hit_obj);

t_mat							*img_xy_sph_cyl_cone(t_hit_pt *hit_pt, \
								t_obj *obj);
t_mat							*img_xy_plane(t_hit_pt *hit_pt, t_obj *obj);
t_mat							*checker_xy_sph_cyl_cone(t_hit_pt *hit_pt, \
								t_obj *obj);
t_mat							*checker_xy_plane(t_hit_pt *hit_pt, t_obj *obj);

double							ft_noise_interpolation_3d(double x, double y, \
								double z);

t_color							*average_color(t_color *dst, int divi);
void							add_color(t_color *dst, t_color *col, int fre);
void							color_init_null(t_color *color);
void							cap_color(t_color *color);

void							find_csg(t_env *e, int i);

void							save_image(char *img, t_env *e);

void							check_parameters(t_env *e);
void							check_materials(t_mat *mat_lst);
void							check_lights(t_light *light_lst);

void							xml_check_img(t_env *e);
void							xml_error_texture(int where, \
								int type, int value);
void							xml_check_tex_id(t_env *e);
void							check_parsing(t_env *e);

void							xml_check_texture_type(int value);
void							xml_check_obj_lst_type(t_env *e);
void							xml_check_obj_id(t_env *e);
void							xml_check_obj_type(int value);
void							xml_check_tex_lst_type(t_env *e);
void							xml_check_obj_norm_type(t_env *e);

#endif
