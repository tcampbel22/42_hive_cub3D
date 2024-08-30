/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 15:37:43 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_img(t_data *data, t_img *img)
{
	safe_delete_img(data, img->mm);
	safe_delete_img(data, img->mm_floor);
	safe_delete_img(data, img->floor);
	safe_delete_img(data, img->ceil);
	safe_delete_img(data, img->pl);
	safe_delete_img(data, img->wall_txt[0]);
	safe_delete_img(data, img->wall_txt[1]);
	safe_delete_img(data, img->wall_txt[2]);
	safe_delete_img(data, img->wall_txt[4]);
	safe_delete_img(data, img->fg_floor);
	safe_delete_img(data, img->fg_ceiling);
	safe_delete_img(data, img->sprite);
	safe_delete_img(data, img->end);
	safe_delete_img(data, img->cage);
	safe_delete_img(data, img->door);
}

//oh-oh, something went wrong, oh well, kill it all and start again ;)
void	armageddon(t_data *data, char *error)
{
	int	i;

	i = -1;
	if (data->mlx)
	{
		free_img(data, data->img);
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	while (++i < 4)
		if (data->wall_text[i])
			ft_nullfree(data->wall_text[i], 0);
	if (data->depth)
		free(data->depth);
	if (data->height)
		free(data->height);
	if (data->sprites)
		free(data->sprites);
	ft_mapfree(data->map);
	if (error)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(error, 2);
		exit(1);
	}
	if (error == NULL)
		printf("Great success!\n");
	exit(0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_ray		ray;
	t_pl		pl;
	t_txt		txt;

	init_all(&data, &ray, &pl, &txt);
	if (parsing(ac, av, &data) != 0)
		armageddon(&data, NULL);
	update_params(&data, &ray);
	mlx_main(&data);
	armageddon(&data, NULL);
	return (0);
}
