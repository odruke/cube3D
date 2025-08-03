#include "cube_test.h"

int test_bad_file(const char *filepath)
{
	int pipefd[2];
	pid_t pid;
	char *buffer;
	t_fd fd;
	int status;
	char *full_path;


	full_path = calloc(sizeof(char), strlen("map/bad/") + strlen(filepath) + 1);
	full_path = strcat(full_path, "map/bad/");
	full_path = strcat(full_path, filepath);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return -1;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}

	if (!pid)
		launch_game(full_path, pipefd);
	else
	{
		close(pipefd[1]);
		child_pid = pid;
		fd.fd = pipefd[0];
		// Set up alarm for timeout
		signal(SIGALRM, signal_handler);
		alarm(TEST_TIMEOUT);
		// sleep(1);
		buffer = NULL;
		buffer = get_next_line(fd, CONTINUE);
		while (buffer)
		{
			if (!strncmp(buffer, "Error:\n", strlen(buffer)))
			{
				get_next_line(fd, RESET_GNL);
				kill(pid, SIGTERM);
				waitpid(pid, &status, 0);
				child_pid = -1;
				free(full_path);
				full_path = NULL;
				return 1; // Test passed - error detected
			}
			free(buffer);
			buffer = NULL;
			buffer = get_next_line(fd, CONTINUE);
		}
		alarm(0); // Cancel alarm

		// If we reach here, no error was found, so we need to kill the process
		kill(pid, SIGTERM);
		waitpid(pid, &status, 0);
		close(pipefd[0]);
		child_pid = -1;
		free(full_path);
		full_path = NULL;
		return 0; // Test failed - no error detected
	}
	return 0;
}

int test_good_file(const char *filepath)
{
	int pipefd[2];
	pid_t pid;
	char *buffer;
	t_fd fd;
	int status;
	char *full_path;


	full_path = calloc(sizeof(char), strlen("map/good/") + strlen(filepath) + 1);
	full_path = strcat(full_path, "map/good/");
	full_path = strcat(full_path, filepath);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return -1;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	if (!pid)
		launch_game(full_path, pipefd);
	else
	{
		close(pipefd[1]);
		child_pid = pid;
		fd.fd = pipefd[0];
		// Set up alarm for timeout
		signal(SIGALRM, signal_handler);
		alarm(TEST_TIMEOUT);
		// sleep(1);
		buffer = NULL;
		int result = waitpid(pid, &status, WNOHANG);
		if (!result)
		{
			// kill(pid, SIGTERM);
			// system("./esc_sender.sh");  // Run in background
			// send_scp(pid);
			// kill(-SIGUSR1, pid);
			waitpid(pid, &status, 0);
			sleep(1);
			buffer = get_next_line(fd, CONTINUE);
			while (buffer)
			{
				if (!strncmp(buffer, "\033[1;32m✅ Game loop starded \033[0m\n", strlen(buffer)))
				{
					while (buffer)
					{
						buffer = get_next_line(fd, CONTINUE);
						if (buffer && !strncmp(buffer, "\033[1;35m🚪Exiting game\033[0m\n", strlen(buffer)))
						{
							get_next_line(fd, RESET_GNL);
							child_pid = -1;
							free(full_path);
							full_path = NULL;
							return 1; // Test passed - program running
						}
					}
					// If we reach here, the game started but didn't properly ended,
					waitpid(pid, &status, 0);
					close(pipefd[0]);
					child_pid = -1;
					free(full_path);
					full_path = NULL;
					return -2; // Test failed - error detected
				}
				free(buffer);
				buffer = NULL;
				buffer = get_next_line(fd, CONTINUE);
			}
			alarm(0); // Cancel alarm

			// If we reach here, program wasn't launched properly
			waitpid(pid, &status, 0);
			close(pipefd[0]);
			child_pid = -1;
			free(full_path);
			full_path = NULL;
			return 0; // Test failed - error detected
		}
		// If we reach here, program wasn't launched properly
		kill(pid, SIGTERM);
		waitpid(pid, &status, 0);
		close(pipefd[0]);
		child_pid = -1;
		free(full_path);
		full_path = NULL;
		return 0;// Test failed - error detected
	}
	return 0; // Test failed - error detected
}

int test_bad_input(void)
{
	return 1;
}
