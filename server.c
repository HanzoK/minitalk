/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:27 by hanjkim           #+#    #+#             */
/*   Updated: 2024/09/15 16:27:45 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

char	*g_buffer = NULL; // Global buffer pointer for dynamic memory.

// Custom realloc function
/*This function resizes the memory block, copying the data from the old
 block to the new block if it exists.*/
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	copy_size;
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (void *)malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr != 0)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

// Function to process a completed character
/*This function appends a fully received character to the global buffer. 
If the char is the null terminator, it indicates the end, then buffer 
is printed and freed, signaling to client that the message was received.*/
void	process_character(pid_t pid, int *i, char *current_char, int *bit)
{
	char	*new_buffer;

	if (*current_char != 0)
	{
		new_buffer = ft_realloc(g_buffer, *i + 1, (*i + 2) * sizeof(char));
		if (!new_buffer)
			(free(g_buffer), exit(1));
		g_buffer = new_buffer;
		g_buffer[*i] = *current_char;
		(*i)++;
		g_buffer[*i] = '\0';
	}
	else
	{
		if (*i > 0)
			(write(1, g_buffer, *i), write(1, "\n", 1));
		free(g_buffer);
		g_buffer = NULL;
		*i = 0;
		kill(pid, SIGUSR2);
	}
	*current_char = 0;
	*bit = CHAR_BIT * sizeof(*current_char) - 1;
}

// Signal handler function
/*Receives SIGUSR1 and SIGUSR2, which represent the bits of a char
being sent from client. It assembles the char bit-by-bit. Once the bits are 
assembled, char is processed with `process_character()`. Once all bits 
are processed, the server sends an 'OK' signal back to client.*/
void	handle_signal_server(int sig, siginfo_t *info, void *context)
{
	static char	current_char = 0;
	static int	bit = CHAR_BIT * sizeof(current_char) - 1;
	static int	index = 0;

	(void)context;
	if (sig == SIGUSR1)
		current_char += (1 << bit);
	else if (sig == SIGUSR2)
		current_char += 0;
	if (bit == 0)
		process_character(info->si_pid, &index, &current_char, &bit);
	else
		bit--;
	kill(info->si_pid, SIGUSR1);
}

// Set up signal handling
/*Function to configure signal handlers using `sigaction()`. 
It ensures that the server can handle the signals (with flag settings )
coming from client and respond accordingly.*/
void	set_signal_server(void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = 0;
	sa.sa_flags += SA_SIGINFO;
	sa.sa_flags += SA_RESTART;
	sa.sa_flags += SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		(write(2, "Failed to set SIGUSR1 handler\n", 30), exit(1));
	else if (sigaction(SIGUSR2, &sa, NULL) < 0)
		(write(2, "Failed to set SIGUSR2 handler\n", 30), exit(1));
}

// Main server function
int	main(void)
{
	set_signal_server(&handle_signal_server);
	ft_printf("Welcome to my reality, Adventurer...\n");
	ft_printf("Here's the PID you oh so wanted: %d\n", getpid());
	ft_printf("Now take it, and leave me be Mortal.\n");
	while (1)
		pause();
	return (0);
}
