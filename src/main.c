/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 18:41:53 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data  data;
	int     fd[2];

    (void)  argc;
    (void)  **argv;
	data.env_path = envp;
	ft_get_env(&data);
	if (pipe(fd) == -1)
		return (1);
	while (1)
	{
		data.line = readline("prompt>");
		if (!ft_strncmp(data.line, "exit", ft_strlen(data.line) - 1))
			break ;
		// write(fd[1], data.line, ft_strlen(data.line));
		// write(fd[1], "\n", 1);
		data.cmd = ft_try_path(&data, data.line, data.cmd);
		if (data.line)
			ft_exec(&data, data.cmd);
		free(data.line);
	}
	free(data.line);
	close(fd[1]);
	return (0);
}