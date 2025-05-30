/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:40:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 11:01:36 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_color	get_color_at_location(t_cub3d *cub3d, size_t x, size_t y)
{
	if (map_is_floor(cub3d, x, y))
		return (0x606060);
	else if (map_is_void(cub3d, x, y))
		return (0xFF000000);
	else
		return (0xdeb887);
}

static void	fill_minimap_texture(t_cub3d *cub3d, t_texture *minimap)
{
	size_t	x;
	size_t	y;
	t_color	color;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < cub3d->map.width)
		{
			color = get_color_at_location(cub3d, x, y);
			draw_rect(minimap, color, (t_uvec2){x * MINIMAP_TILE_SIZE, y
				* MINIMAP_TILE_SIZE}, (t_uvec2){x * MINIMAP_TILE_SIZE
				+ MINIMAP_TILE_SIZE, y * MINIMAP_TILE_SIZE
				+ MINIMAP_TILE_SIZE});
			x++;
		}
		y++;
	}
}

static bool	create_minimap_texture(t_cub3d *cub3d)
{
	t_img	*minimap;

	minimap = mlx_new_image(cub3d->mlx, cub3d->map.width * MINIMAP_TILE_SIZE,
			cub3d->map.height * MINIMAP_TILE_SIZE);
	if (!minimap)
		return (_error("failed to create minimap image !"), true);
	fill_minimap_texture(cub3d, minimap);
	add_asset(cub3d, __TEXTURE_MINIMAP__, minimap);
	return (false);
}

bool	init_minimap(t_cub3d *cub3d)
{
	t_texture	*border;
	t_texture	*player;

	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	player = get_texture(cub3d, TEXTURE_MINIMAP_PLAYER);
	cub3d->minimap.border_pos = (t_uvec2){MINIMAP_OFFSET, SCREEN_H
		- border->height - MINIMAP_OFFSET};
	cub3d->minimap.player_pos = (t_uvec2){MINIMAP_OFFSET + border->width / 2
		- player->width / 2, SCREEN_H - border->height / 2 - MINIMAP_OFFSET
		- player->height / 2};
	if (create_minimap_texture(cub3d) == true)
		return (true);
	return (false);
}
