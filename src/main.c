/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/03/27 14:31:22 by chsiffre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	int			fd[2];

    (void)  argc;
    (void)  **argv;
	prompt.env_path = envp;
	ft_get_env(&prompt);
	if (pipe(fd) == -1)
		return (1);
	while (1)
	{
		write(1, "prompt>", 8);
		prompt.line = get_next_line(1);
		if (!ft_strncmp(prompt.line, "exit", ft_strlen(prompt.line) - 1))
			break ;
		write(fd[1], prompt.line, ft_strlen(prompt.line));
		write(fd[1], "\n", 1);
		prompt.line = ft_try_path(&prompt, prompt.line);
		if (prompt.line)
			ft_exec(&prompt, prompt.line);
		free(prompt.line);
	}
	free(prompt.line);
	close(fd[1]);
	return (0);
}