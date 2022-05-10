/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 03:57:25 by lrosby            #+#    #+#             */
/*   Updated: 2022/01/22 03:57:28 by lrosby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*check(char **path, char *commands)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, commands);
		free(tmp);
		if (access (tmp2, 1) == -1)
			free(tmp2);
		else
			break ;
	}
	return (tmp2);
}

void	path_commands(char **envp, char *av_com)
{
	char	**str;
	char	**commands;
	char	*path;
	int		i;

	str = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			str = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	commands = ft_split(av_com, ' ');
	path = check(str, *commands);
	execve(path, commands, envp);
	write(2, "Command not found.\n", 19);
	exit (0);
}

void	first_process(char *file, char *av_com, char **envp, int *pip)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "File not found.\n", 16);
		exit (0);
	}
	dup2(fd, 0);
	dup2(pip[1], 1);
	close(fd);
	close(pip[1]);
	close(pip[0]);
	path_commands(envp, av_com);
}

void	last_process(char *file, char *av_com, char **envp, int *pip)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		write(2, "File not found.\n", 16);
		exit (0);
	}
	dup2(fd, 1);
	dup2(pip[0], 0);
	close(fd);
	close(pip[0]);
	close(pip[1]);
	path_commands(envp, av_com);
}

int	main(int argc, char **argv, char **envp)
{
	int	pip[2];
	int	fk;

	if (argc < 5)
	{
		write(2, "Conditions not met.\n", 20);
		return (0);
	}
	if (pipe(pip) == -1)
		return (0);
	fk = fork();
	if (fk == -1)
		write(2, "ERROR FORK\n", 11);
	if (fk == 0)
		first_process(argv[1], argv[2], envp, pip);
	else
		last_process(argv[4], argv[3], envp, pip);
	return (0);
}
