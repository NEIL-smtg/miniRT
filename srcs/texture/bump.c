/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:56:28 by suchua            #+#    #+#             */
/*   Updated: 2023/08/07 01:12:12 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_bump_offset(double u, double v)
{
	double	offset;

	offset = sin(u * 2 * M_PI) * sin(v * 2 * M_PI);
	// offset *= random_range(0.8, 1.2) * random_range(0.8, 1.2);
	return (offset);
}

t_vec3 CalculateUVTangent(const t_vec3 normal, t_vec3 gl) {
    t_vec3 reference = gl;// Use the world space X axis as reference
    t_vec3 tangent = normalize(vec3_cross(reference, normal));
    t_vec3 uv_tangent = normalize(vec3_cross(normal, gl));
    return uv_tangent;
}

// Function to calculate bump offset based on bump map value
t_vec3 CalculateBumpOffset(const t_vec3 *normal, const t_vec3 *u_tangent, const t_vec3 *v_tangent, 
                           double u, double v, double bump_value, double bump_strength) {
    // Calculate rate of change along u and v directions (approximated)
    double u_rate_of_change = u;
    double v_rate_of_change = v;

    // Calculate the bump offset in tangent space
    t_vec3 bump_offset;
    bump_offset.x = u_rate_of_change * bump_strength * bump_value;
    bump_offset.y = v_rate_of_change * bump_strength * bump_value;
    bump_offset.z = 0.0; // Assuming no displacement in the normal direction

    // Transform bump offset from tangent space to object space
    t_vec3 perturbed_normal;
    perturbed_normal.x = bump_offset.x * u_tangent->x + bump_offset.y * v_tangent->x + bump_offset.z * normal->x;
    perturbed_normal.y = bump_offset.x * u_tangent->y + bump_offset.y * v_tangent->y + bump_offset.z * normal->y;
    perturbed_normal.z = bump_offset.x * u_tangent->z + bump_offset.y * v_tangent->z + bump_offset.z * normal->z;

    // Normalize the perturbed normal
    double length = sqrt(perturbed_normal.x * perturbed_normal.x + 
                         perturbed_normal.y * perturbed_normal.y + 
                         perturbed_normal.z * perturbed_normal.z);
    
    perturbed_normal.x /= length;
    perturbed_normal.y /= length;
    perturbed_normal.z /= length;

    return perturbed_normal;
}


t_vec3	get_bump_effect_normal(t_obj *obj, const t_vec3 inter, t_vec3 n, \
		t_img texture)
{
	double	u;
	double	v;
	t_vec3	bump_offset;
	double	bump_val;
	t_vec3	perbuted_n;

	if (!obj->bump || !texture.ptr)
		return (n);
	obj->get_uv(&inter, &u, &v, obj);
	u = nb_clamp(u, 0, 1);
	v = nb_clamp(v, 0, 1);
	bump_val = texture.bump_map[(int) u * texture.width][(int) v * texture.height];
	t_vec3	utan, vtan;
	utan = CalculateUVTangent(n, new_vec3(1, 0 ,0));
	vtan = CalculateUVTangent(n, new_vec3(0, 1, 0));
	bump_offset = CalculateBumpOffset(&n, &utan, &vtan, u, v, bump_val, 0.8);
	perbuted_n = vec3_add(n, bump_offset);
	return (normalize(perbuted_n));
}
