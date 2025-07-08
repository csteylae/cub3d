/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:27:07 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/08 11:27:11 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	polish_list(t_lst **lst)
{
	t_lst	*last_node;
	t_lst	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_lst));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*lst);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(lst, clean_node, buf);
}

char	*get_line(t_lst *lst)
{
	int		str_len;
	char	*next_str;

	if (lst == NULL)
		return (NULL);
	str_len = len_to_newline(lst);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(lst, next_str);
	return (next_str);
}

void	append(t_lst **lst, char *buf)
{
	t_lst	*new_node;
	t_lst	*last_node;

	last_node = find_last_node(*lst);
	new_node = malloc(sizeof(t_lst));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_lst **lst, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*lst))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf [char_read] = '\0';
		append(lst, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_lst	*lst = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	next_line = get_line(lst);
	polish_list(&lst);
	return (next_line);
}
