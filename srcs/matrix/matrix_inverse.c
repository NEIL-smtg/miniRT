/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 02:08:19 by suchua            #+#    #+#             */
/*   Updated: 2023/08/09 23:50:47 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdbool.h>
#include "../../Libft/include/libft.h"

double	invf(int i, int j, const double *m)
{
	int		o;
	double	inv;

	o = 2 + (j - i);
	i += 4 + o;
	j += 4 - o;
	inv = m[((j + 1) % 4) * 4 + ((i - 1) % 4)] * m[(j % 4) * 4 + (i % 4)]
		* m[((j - 1) % 4) * 4 + ((i + 1) % 4)]
		+ m[((j + 1) % 4) * 4 + ((i + 1) % 4)] * m[(j % 4) * 4 + ((i - 1) % 4)]
		* m[((j - 1) % 4) * 4 + (i % 4)]
		+ m[((j - 1) % 4) * 4 + ((i - 1) % 4)] * m[((j + 1) % 4) * 4 + (i % 4)]
		* m[(j % 4) * 4 + ((i + 1) % 4)]
		- m[((j - 1) % 4) * 4 + ((i - 1) % 4)] * m[(j % 4) * 4 + (i % 4)]
		* m[((j + 1) % 4) * 4 + ((i + 1) % 4)]
		- m[((j - 1) % 4) * 4 + ((i + 1) % 4)] * m[(j % 4) * 4 + ((i - 1) % 4)]
		* m[((j + 1) % 4) * 4 + (i % 4)]
		- m[((j + 1) % 4) * 4 + ((i - 1) % 4)] * m[((j - 1) % 4) * 4 + (i % 4)]
		* m[(j % 4) * 4 + ((i + 1) % 4)];
	if (o % 2)
		return (inv);
	return (-inv);
}

bool	inverse_matrix4x4(const double *m, double *out)
{
	double	inv[16];
	int		c[3];
	double	d;

	d = 0;
	c[0] = -1;
	while (++c[0] < 4)
	{
		c[1] = -1;
		while (++c[1] < 4)
			inv[c[1] * 4 + c[0]] = invf(c[0], c[1], m);
	}
	c[2] = -1;
	while (++c[2] < 4)
		d += m[c[2]] * inv[c[2] * 4];
	if (d == 0.0f)
		return (false);
	d = 1.0 / d;
	c[0] = -1;
	while (++c[0] < 16)
		out[c[0]] = inv[c[0]] * d;
	return (true);
}

double	*mat4_to_int4(t_mat4 mat)
{
	double	*m;

	m = ft_calloc(16, sizeof(double));
	m[0] = mat.r1.x;
	m[1] = mat.r1.y;
	m[2] = mat.r1.z;
	m[3] = mat.r1.w;
	m[4] = mat.r2.x;
	m[5] = mat.r2.y;
	m[6] = mat.r2.z;
	m[7] = mat.r2.w;
	m[8] = mat.r3.x;
	m[9] = mat.r3.y;
	m[10] = mat.r3.z;
	m[11] = mat.r3.w;
	m[12] = mat.r4.x;
	m[13] = mat.r4.y;
	m[14] = mat.r4.z;
	m[15] = mat.r4.w;
	return (m);
}

t_mat4	int4_to_mat4(double *out)
{
	t_mat4	new;

	new.r1 = new_vec4(out[0], out[1], out[2], out[3]);
	new.r2 = new_vec4(out[4], out[5], out[6], out[7]);
	new.r3 = new_vec4(out[8], out[9], out[10], out[11]);
	new.r4 = new_vec4(out[12], out[13], out[14], out[15]);
	free(out);
	return (new);
}

t_mat4	inverse_mat4(t_mat4 mat)
{
	double	*m;
	double	*out;
	bool	inverted;

	out = ft_calloc(16, sizeof(double));
	m = mat4_to_int4(mat);
	inverted = inverse_matrix4x4(m, out);
	free(m);
	if (!inverted)
		exit(0);
	return (int4_to_mat4(out));
}
