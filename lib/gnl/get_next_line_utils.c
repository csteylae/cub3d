/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:27:38 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/08 11:27:41 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_lst *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i] && i < BUFFER_SIZE)
		{
			if (lst->str_buf[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

t_lst	*find_last_node(t_lst	*lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	len_to_newline(t_lst *lst)
{
	int	i;
	int	len;

	if (lst == NULL)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i])
		{
			if (lst->str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

void	copy_str(t_lst *lst, char *str)
{
	int	i;
	int	k;

	if (lst == NULL)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i])
		{
			if (lst->str_buf[i] == '\n' && lst->next != NULL)
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			if (lst->str_buf[i] == '\n' && lst->next == NULL)
				break ;
			str[k++] = lst->str_buf[i++];
		}
		lst = lst->next;
	}
	str[k] = '\0';
}

void	dealloc(t_lst **lst, t_lst *clean_node, char *buf)
{
	t_lst	*tmp;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str_buf);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node->str_buf[0])
		*lst = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
