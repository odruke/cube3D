#include "cube_test.h"

// Function to safely allocate and initialize file_list_t
file_list_t* allocate_file_list()
{
    file_list_t *list = malloc(sizeof(file_list_t));
    if (!list)
    {
        printf(RED "Error: Failed to allocate memory for file list\n" RESET);
        return NULL;
    }

    // Allocate memory for the array of string pointers
    list->files = malloc(sizeof(char*) * MAX_FILES);
    if (!list->files)
    {
        printf(RED "Error: Failed to allocate memory for file array\n" RESET);
        free(list);
        return NULL;
    }

    // Initialize all pointers to NULL
    for (int i = 0; i < MAX_FILES; i++)
        list->files[i] = NULL;

    list->count = 0;
    return list;
}

// Function to safely free file_list_t
void free_file_list(file_list_t *list)
{
    if (!list)
        return;

    if (list->files)
    {
        // Free all individual file strings
        for (int i = 0; i < list->count; i++)
        {
            if (list->files[i])
            {
                free(list->files[i]);
                list->files[i] = NULL;
            }
        }
        // Free the array of pointers
        free(list->files);
        list->files = NULL;
    }

    // Free the structure itself
    free(list);
}

int main()
{
	file_list_t *bad_files = NULL;
	file_list_t *good_files = NULL;
	int bad_passed = 0, bad_total = 0;
	int good_passed = 0, good_total = 0;

	printf(YELLOW "cub3D Automatic Tester\n" RESET);
	printf("======================\n\n");

	// Check if cub3D executable exists
	if (access("../cub3D", X_OK) != 0) {
		printf(RED "Error: ./cub3D executable not found or not executable!\n" RESET);
		printf("Make sure to compile your project first: make\n");
		return 1;
	}

	// Allocate memory for file lists
	bad_files = allocate_file_list();
	if (!bad_files)
		return 1;

	good_files = allocate_file_list();
	if (!good_files)
	{
		free_file_list(bad_files);
		return 1;
	}

	print_header("TESTING BAD FILES (Should show errors)");

	if (scan_directory("../map/bad", bad_files) < 0)
	{
		printf(RED "Error: Cannot scan bad files directory\n" RESET);
		free_file_list(bad_files);
		free_file_list(good_files);
		return 1;
	}

	bad_total = bad_files->count;
	printf("Found %d bad test files\n\n", bad_total);

	for (int i = 0; i < bad_files->count; i++)
	{
		int result = test_bad_file(bad_files->files[i]);
		if (result == 1) {
			bad_passed++;
			print_test_result(bad_files->files[i], 1, "Error correctly detected");
		} else if (result == 0) {
			print_test_result(bad_files->files[i], 0, "ERROR: File was accepted!");
		} else {
			print_test_result(bad_files->files[i], 0, "Test execution failed");
		}
	}

	// Test good files
	print_header("TESTING GOOD FILES (Should run without errors)");

	if (scan_directory("../map/good", good_files) < 0)
	{
		printf(RED "Error: Cannot scan good files directory\n" RESET);
		free_file_list(bad_files);
		free_file_list(good_files);
		return 1;
	}

	good_total = good_files->count;
	printf("Found %d good test files\n\n", good_total);

	for (int i = 0; i < good_files->count; i++)
	{
		int result = test_good_file(good_files->files[i]);
		if (result == 1) {
			good_passed++;
			print_test_result(good_files->files[i], 1, "Program started successfully");
		} else if (result == 0) {
			print_test_result(good_files->files[i], 0, "ERROR: File was rejected!");
		} else {
			print_test_result(good_files->files[i], 0, "Test execution failed");
		}
	}

	print_header("TEST SUMMARY");
	printf("Bad Files:  %s%d/%d passed%s (files correctly rejected)\n",
			bad_passed == bad_total ? GREEN : RED, bad_passed, bad_total, RESET);
	printf("Good Files: %s%d/%d passed%s (files correctly accepted)\n",
			good_passed == good_total ? GREEN : RED, good_passed, good_total, RESET);
	printf("Total:      %s%d/%d tests passed%s\n\n",
			(bad_passed + good_passed) == (bad_total + good_total) ? GREEN : RED,
			bad_passed + good_passed, bad_total + good_total, RESET);

	if ((bad_passed + good_passed) == (bad_total + good_total))
		printf(GREEN "🎉 All tests passed! Your cub3D parser is working correctly!\n" RESET);
	else
		printf(RED "❌ Some tests failed. Check your parser implementation.\n" RESET);

	free_file_list(bad_files);
	free_file_list(good_files);
	return 0;
}
