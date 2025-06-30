#include "../../../inc/cub3D.h"

int	maps_content(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int parse_map(t_data *game, char **lines)
{
	int	i;
	int	j;
	int	found_map_start;
	int	found_gap;

	i = -1;
	j = 0;
	found_map_start = 0;
	found_gap = 0;
	game->nb_map_lines = 0;
	while (lines[++i])
	{
		if (!maps_content(lines[i]))
			ft_free_error("Error\nWrong element in map!\n", game);

		if (ft_strlen(lines[i]) > 0 && lines[i][0] != '\n')//Checker si ma ligne est vide et != \n.
		{
			if (found_gap)//Si == 1 alors il y a un trou dans ma map.
				ft_free_error("Error\nMap contains gap (empty line inside)!\n", game);
			found_map_start = 1;
			game->nb_map_lines++;
		}
		else if (found_map_start)
			found_gap = 1;
	}
	if (game->nb_map_lines == 0)
		ft_error("Error\nWhere is the map?\n");
	game->map = malloc(sizeof(char *) * (game->nb_map_lines + 1));//Allocation pour map.
	if (!game->map)
		ft_error("Error\nMalloc failed!\n");
	i = -1;
	while (lines[++i])
	{
		if (ft_strlen(lines[i]) > 0 && lines[i][0] != '\n')
		{
			game->map[j] = ft_strdup(lines[i]);
			if (!game->map[j])
				ft_error("Error\nStrdup failed!\n");
			j++;
		}
	}
	game->map[j] = NULL;
	return (1);
}
