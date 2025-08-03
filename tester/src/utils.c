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

void	launch_game(char *full_path, int *pipefd)
{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (chdir("..") != 0)
		{
			perror("chdir");
			exit(1);
		}
		execl("/usr/bin/stdbuf", "stdbuf", "-o0", "-e0", "./cub3D", full_path, NULL);
		execl("./cub3D", "cub3D", full_path, NULL);
		perror("execl");
		exit(1);
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
