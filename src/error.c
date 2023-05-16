/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:39:01 by lucas             #+#    #+#             */
/*   Updated: 2023/05/16 14:48:39 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_print_error(char *str)
{
	char	*join;

	join = ft_strjoin("bash : ", str);
	perror(join);
	free(join);
	return (1);
}

int	ft_cmd_error(char *str)
{
	char	*join;

	join = ft_strjoin(str, ": command not found\n");
	write(2, join, ft_strlen(join));
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