/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:50:29 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/22 18:43:10 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

int main(int argc, char **argv, char **env)
{
	int i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	errno = 0;
	//perror(NULL);
	//strerror(errno);
}
