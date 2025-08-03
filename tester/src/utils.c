#include "cube_test.h"

// Global variable to store child PID for signal handling
pid_t child_pid = -1;

void signal_handler(int sig)
{
	(void)sig;
	if (child_pid > 0)
	{
		kill(child_pid, SIGTERM);
		waitpid(child_pid, NULL, 0);
	}
}

void free_files(file_list_t *filestruct)
{
	for (int i = 0; i < filestruct->count; i++)
	{
		if (filestruct->files[i])
		{
			free(filestruct->files[i]);
			filestruct->files[i] = NULL;
		}
	}
	filestruct->count = 0;
}

int scan_directory(const char *dir_path, file_list_t *files)
{
	DIR *dir;
	struct dirent *entry;

	if (!files || !files->files)
	{
		printf(RED "Error: Invalid file list structure\n" RESET);
		return -1;
	}

	dir = opendir(dir_path);
	if (!dir)
	{
		printf(RED "Error: Cannot open directory %s\n" RESET, dir_path);
		return -1;
	}

	files->count = 0;

	// Initialize all pointers to NULL for safety
	for (int i = 0; i < MAX_FILES; i++)
		files->files[i] = NULL;

	while ((entry = readdir(dir)) != NULL && files->count < MAX_FILES - 1)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		files->files[files->count] = strdup(entry->d_name);
		if (!files->files[files->count])
		{
			printf(RED "Error: Memory allocation failed for filename\n" RESET);
			closedir(dir);
			return -1;
		}
		files->count++;
	}

	closedir(dir);
	return files->count;
}

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
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return -1;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}

	if (pid == 0)
	{
		// Child process
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (chdir("..") != 0)
		{
			perror("chdir");
			exit(1);
		}

		execl("cub3D", "cub3D", full_path, NULL);
		perror("execl");
		exit(1);
	}
	else
	{
		// Parent process
		close(pipefd[1]);
		child_pid = pid;
		fd.fd = pipefd[0];
		// Set up alarm for timeout
		signal(SIGALRM, signal_handler);
		alarm(TEST_TIMEOUT);
		sleep(1);
		free(full_path);
		full_path = NULL;
		buffer = NULL;
		buffer = get_next_line(fd, CONTINUE);
		while (buffer)
		{

			// if (!strncmp(buffer, "✅ Mlx connection establised", strlen(buffer)))
			if (!strncmp(buffer, "Error:\n", strlen(buffer)))
			{
				// while (buffer)
				// {
				// 	printf("%s\n", buffer);
				// 	buffer = get_next_line(fd, CONTINUE);
				// }
				get_next_line(fd, RESET_GNL);
				kill(pid, SIGTERM);
				waitpid(pid, &status, 0);
				child_pid = -1;
				return 1; // Test passed - error detected
			}
			free(buffer);
			buffer = NULL;
			buffer = get_next_line(fd, CONTINUE);

		}
		// Read output
		// ssize_t bytes_read = read(pipefd[0], buffer, BUFFER_SIZE - 1);
		alarm(0); // Cancel alarm

		// if (bytes_read > 0)
		// {
		// 	buffer[bytes_read] = '\0';

		// 	// Check if "Error" is in the output
		// 	if (strstr(buffer, "Error") != NULL)
		// 	{
		// 		close(pipefd[0]);
		// 		waitpid(pid, &status, 0);
		// 		child_pid = -1;
		// 		return 1; // Test passed - error detected
		// 	}
		// }

		// If we reach here, no error was found, so we need to kill the process
		kill(pid, SIGTERM);
		waitpid(pid, &status, 0);
		close(pipefd[0]);
		child_pid = -1;

		return 0; // Test failed - no error detected
	}
}

int test_good_file(const char *filepath)
{
	char command[1024];
	snprintf(command, sizeof(command), "cd .. && timeout 2s ./cub3D '%s' >/dev/null 2>&1", filepath);

	int result = system(command);
	int exit_code = WEXITSTATUS(result);

	// If exit code is 124, it's a timeout (good for good files - means program started)
	if (exit_code == 124) {
		return 1; // PASS - program started and was killed by timeout
	}
	return 0; // FAIL - program exited immediately (probably error)
}

void print_header(const char *title)
{
	printf("\n" BLUE "================================\n");
	printf("  %s\n", title);
	printf("================================\n" RESET);
}

void print_test_result(const char *filename, int passed, const char *type)
{
	const char *basename = strrchr(filename, '/');
	basename = basename ? basename + 1 : filename;

	if (passed) {
		printf(GREEN "✓ PASS" RESET " - %s: %s\n", type, basename);
	} else {
		printf(RED "✗ FAIL" RESET " - %s: %s\n", type, basename);
	}
}
