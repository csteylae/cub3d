#include "../../../inc/cub3D.h"

static char **read_lines(char *file)
{
	char	**lines;
	char	*line;
	int		count;
	int		i;
	int		fd;

	count = 0;
	i = 0;
	fd = open(file, O_RDONLY);//Ouvrir une première fois pour compter les lignes.
	if (fd == -1)
		ft_error("Error\nFile opening failure!\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	if (count == 0)
		ft_error("Error\nFile must contain something!\n");
	fd = open(file, O_RDONLY);//Ouvir une 2eme fois afin de stocker.
	if (fd == -1)
		ft_error("Error\nFailure reopening file\n");
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
	{
		ft_error("Error\nMalloc failed\n"); 
		close(fd);
	}
	while ((line = get_next_line(fd)) != NULL)
		lines[i++] = line;
	lines[i] = NULL;
	close(fd);
	return (lines);
}

void	parse(t_data *game, char *file)
{
	char	**lines;
	char	*trimmed;
	int		i;

	i = 0;
	lines = read_lines(file);
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], " ");
		if (ft_strlen(trimmed) > 0)
		{
			if (!check_texture(game, trimmed))
			{
				free(trimmed);
				break;
			}
		}
		free(trimmed);
		i++;
	}
	check_texture_exist(game);
	if (!parse_map(game, &lines[i]))
		ft_free_error("Error\nMap parsing has failed!\n", game);
	//i = 0;
	//while (game->map[i])
	//	printf("%s\n", game->map[i++]);
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
