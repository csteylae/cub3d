#include "../../../inc/cub3D.h"

char	**copy_map(char **src_map)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	while (src_map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (src_map[++i])
	{
		copy[i] = ft_strdup(src_map[i]);
		if (!copy[i])
		{
			j = -1;
			while (++j < i)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}
