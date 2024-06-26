/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:15:03 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/05 14:07:35 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Counts the objects in the scene, and allocates the objects array
 * and return -1 if there was an error
 * else 0
 *
 * @return int
 */
static int	init_objects(void)
{
	char	*line;
	int		fd;

	fd = open(get_program()->file_name, O_RDONLY);
	if (fd < 0)
		return (perror(PROGRAM_NAME), -1);
	line = ft_get_next_line_nonl(fd);
	while (line)
	{
		if (line[0] && line[0] != '#')
			get_program()->object_count++;
		free(line);
		line = ft_get_next_line_nonl(fd);
	}
	if (close(fd) < 0)
		return (perror(PROGRAM_NAME), -1);
	get_program()->objects = ft_calloc(get_program()->object_count,
		sizeof(t_scene_object));
	if (!get_program()->objects)
		return (set_error((char *)__func__, ALLOC), -1);
	return (0);
}

/**
 * @brief Creates and saves the current line as a scene_object
 *
 * @param line
 * @return int
 */
static int	save_object(char *line, uint8_t *unique_obj_count)
{
	char		**splt;
	static int	count = 0;
	int			type;
	int			res;

	splt = ft_split(line, SPACE);
	if (!splt)
		return (set_error((char *)__func__, ALLOC), -1);
	type = get_object_type(splt[0]);
	if (type < 0)
		return (free_arr(splt, -1, 1), -1);
	if (type == AMBIENT_LIGHT && (*unique_obj_count & UNIQUE_OBJ_COUNT_A))
		return (rt_perror((char *)__func__, TOO_MUCH_AMBIENT_LIGHT),
			free_arr(splt, -1, 1), -1);
	*unique_obj_count |= ((type == AMBIENT_LIGHT) * UNIQUE_OBJ_COUNT_A);
	if (type == CAMERA && (*unique_obj_count & UNIQUE_OBJ_COUNT_C))
		return (rt_perror((char *)__func__, TOO_MUCH_CAMERA),
			free_arr(splt, -1, 1), -1);
	*unique_obj_count |= ((type == CAMERA) * UNIQUE_OBJ_COUNT_C);
	res = get_obj_creator()[type](&get_program()->objects[count++],
			get_length(splt), splt);
	return (free_arr(splt, -1, 1), res);
}

/**
 * @brief Reads the .rt scene file & saves the objects along the way
 *
 * @return int
 */
static int	read_file(uint8_t *unique_obj_count)
{
	char	*line;
	int		fd;
	int		count;

	fd = open(get_program()->file_name, O_RDONLY);
	if (fd < 0)
		return (perror(PROGRAM_NAME), -1);
	line = ft_get_next_line_nonl(fd);
	count = -1;
	while (line)
	{
		if (line[0] && line[0] != '#' && ++count > -1
			&& save_object(line, unique_obj_count) < 0)
			return (free(line), part_cleanup_program(count), -1);
		free(line);
		line = ft_get_next_line_nonl(fd);
	}
	if (close(fd) < 0)
		return (perror(PROGRAM_NAME), -1);
	return (0);
}

int	parse_input(void)
{
	uint8_t	unique_objects_count;

	unique_objects_count = 0b0;
	if (init_objects() < 0)
		return (-1);
	if (read_file(&unique_objects_count) < 0)
		return (free(get_program()->objects), -1);
	if (!(unique_objects_count & UNIQUE_OBJ_COUNT_C))
		return (rt_perror((char *)__func__, NO_CAMERA), cleanup_program(), -1);
	return (0);
}
