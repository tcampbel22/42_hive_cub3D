/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:08:28 by clundber          #+#    #+#             */
/*   Updated: 2024/07/19 16:24:01 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	wall_dist(t_data *data, t_ray *ray)
{
	float	horizontal_dist;
	float	vertical_dist;

	vertical_dist = 0;
	horizontal_dist = 0;
	//HORIZONTAL
	if (ray->ray_orient == 0 || ray->ray_orient == PI || ray->ray_orient == (2 * PI))
		horizontal_dist += data->fov_depth + 100;
	if (ray->ray_orient < 180) //ray facing down, tan is inverted
	{
		ray->ray_y = ceilf(data->player_y);
		ray->ray_x = data->player_x + ((ceilf(data->player_y) - data->player_y) * -tan(ray->ray_orient));
	}
	else //ray facing up
	{
		ray->ray_y = floorf(data->player_y);
		ray->ray_x = data->player_x + ((data->player_y - floorf(data->player_y)) * tan(ray->ray_orient)); 
	}
	printf("p_x = %f p_y = %f\nr_x = %f r_y = %f\n", data->player_x, data->player_y, ray->ray_x, ray->ray_y);
	return (horizontal_dist);

	//VERTICAL
}
// Delete later? :D
void	print_penis(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	
 	while (i < 20)
	{
		mlx_put_pixel(data->images->ray_grid, ((data->player_x * data->scale) + i) * sin(data->p_orientation), ((data->player_y * data->scale) - i) * cos(data->p_orientation), make_color(255, 0, 0, 255));
		i++;
	}
}

void	ray_main(void *param)
{
	float	dist;
	t_data	*data;

	data = param;
	dist = 0;
	data->ray->ray_orient = data->p_orientation;
	dist = wall_dist(data, data->ray);
	mlx_image_to_window(data->mlx, data->images->ray_grid, 0, 0);
	//mlx_delete_image(data->mlx, data->images->ray_grid);
	print_penis(data);
}