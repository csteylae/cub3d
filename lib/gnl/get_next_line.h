/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:27:23 by csteylae          #+#    #+#             */
/*   Updated: 2025/07/08 11:27:27 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_lst
{
	char			*str_buf;
	struct s_lst	*next;
}				t_lst;

char	*get_next_line(int fd);
char	*get_line(t_lst *lst);
void	create_list(t_lst **lst, int fd);
void	append(t_lst **lst, char *buf);
void	copy_str(t_lst *lst, char *str);
void	polish_list(t_lst **lst);
void	dealloc(t_lst **lst, t_lst *clean_node, char *buf);
int		len_to_newline(t_lst *lst);
int		found_newline(t_lst *lst);
t_lst	*find_last_node(t_lst	*lst);

#endif
