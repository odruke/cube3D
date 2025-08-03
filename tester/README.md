# cub3D Automatic Tester

This is an automatic testing program for the cub3D project that validates your parser against good and bad input files.

## Features

- **Automated Testing**: Tests all files in `map/good/` and `map/bad/` directories
- **Error Detection**: Detects if your program correctly rejects invalid files
- **Success Validation**: Ensures valid files are accepted and the program runs
- **Colored Output**: Clear visual feedback with colored pass/fail indicators
- **Timeout Protection**: Prevents hanging on problematic files
- **Comprehensive Reporting**: Detailed summary of test results

## How It Works

### Bad Files Testing
1. Runs `./cub3D` with each bad file
2. Captures stdout/stderr output
3. Looks for "Error" in the output
4. **PASS**: If error is found (file correctly rejected)
5. **FAIL**: If no error found (file wrongfully accepted)

### Good Files Testing
1. Runs `./cub3D` with each good file
2. Waits 1 second for program to initialize
3. Checks if program is still running
4. **PASS**: If program runs successfully (file accepted)
5. **FAIL**: If program exits immediately (file wrongfully rejected)

## Usage

1. **Compile the tester**:
   ```bash
   cd tester
   make
   ```

2. **Run from the main cub3D directory**:
   ```bash
   cd ..
   ./tester/test_cub3d
   ```

   Or run from tester directory:
   ```bash
   cd tester
   ../test_cub3d
   ```

## Requirements

- Your `cub3D` executable must be compiled and present in the main directory
- Test files must be in `map/good/` and `map/bad/` directories
- Your program should output "Error" (case-sensitive) when rejecting invalid files

## Output Format

```
cub3D Automatic Tester
======================

================================
  TESTING BAD FILES (Should show errors)
================================
Found 16 bad test files

✓ PASS - Error correctly detected: wrong_extension.txt
✓ PASS - Error correctly detected: missing_north_texture.cub
✗ FAIL - ERROR: File was accepted!: some_file.cub

================================
  TESTING GOOD FILES (Should run without errors)
================================
Found 9 good test files

✓ PASS - Program started successfully: valid_basic.cub
✓ PASS - Program started successfully: minimal_valid.cub

================================
  TEST SUMMARY
================================
Bad Files:  15/16 passed (files correctly rejected)
Good Files: 9/9 passed (files correctly accepted)
Total:      24/25 tests passed

❌ Some tests failed. Check your parser implementation.
```

## Troubleshooting

- **"./cub3D executable not found"**: Make sure to compile your main project first
- **Tests hanging**: The tester has a 3-second timeout protection
- **False positives**: Ensure your error messages contain the word "Error"

## Files Tested

The tester automatically discovers and tests all `.cub` files in:
- `map/good/` - Valid files that should be accepted
- `map/bad/` - Invalid files that should be rejected

## Compilation

```bash
make        # Compile the tester
make clean  # Remove object files
make fclean # Remove executable
make re     # Recompile everything
```
