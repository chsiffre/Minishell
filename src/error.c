/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:39:01 by lucas             #+#    #+#             */
/*   Updated: 2023/05/09 22:27:17 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_print_error(char	*str)
{
	char	*join;

	join = ft_strjoin("bash : ", str);
	perror(join);
	free(join);
	return (1);
}

/*
int	ft_error(t_pipe *pipex)
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	ft_end(pipex, 1);
	exit(1);
}
*/