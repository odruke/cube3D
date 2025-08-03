# cub3D Automatic Tester - Alpha v0.1

🚧 **This is a first alpha version of the tester that awaits future updates to include additional tests and improved ESC key management.**

An automated testing program for the cub3D project that validates your parser and basic functionality against good and bad input files.

## Features

- **Parser Validation**: Tests error detection for invalid `.cub` files
- **Basic Functionality**: Verifies that valid files can start the game loop
- **Colored Output**: Clear visual feedback with pass/fail indicators
- **Timeout Protection**: Prevents hanging on problematic files
- **Comprehensive Reporting**: Detailed summary of test results

## Prerequisites

### Required cub3D Output Messages

Your cub3D program **must** output these exact messages for the tester to work correctly:

1. **Error Messages** (for parsing errors):
   ```
   Error:\n
   [your custom error message]
   ```
   **Important**: Must start with exactly `"Error:\n"` followed by your description.

2. **Game Loop Start** (when successfully entering the main loop):
   ```
   \033[1;32m✅ Game loop starded \033[0m\n
   ```

3. **Clean Exit** (when exiting normally):
   ```
   \033[1;35m🚪Exiting game\033[0m\n
   ```

### Required Directory Structure

```
cub3D/
├── cub3D                 # Your compiled executable
├── map/
│   ├── good/             # Valid .cub files (should be accepted)
│   │   ├── valid_basic.cub
│   │   ├── minimal_valid.cub
│   │   └── ...
│   └── bad/              # Invalid .cub files (should be rejected)
│       ├── missing_texture.cub
│       ├── wrong_format.cub
│       └── ...
└── tester/
    ├── cube_tester       # The tester executable
    └── ...
```

## How It Works

### Bad Files Testing (Automatic)
1. Runs `./cub3D` with each bad file
2. Captures program output
3. Looks for `"Error:\n"` in the output
4. Program exits automatically after error detection
5. **PASS**: If error message found (file correctly rejected)
6. **FAIL**: If no error found (file wrongfully accepted)

### Good Files Testing (Semi-Manual)
1. Runs `./cub3D` with each good file
2. Waits for game initialization
3. Looks for the game loop confirmation message
4. **User Interaction Required**: Press ESC within 3 seconds to exit normally
5. If no ESC pressed, program force-closes after timeout
6. **PASS**: If game starts and exits properly
7. **FAIL**: If game crashes or fails to start

⚠️ **Note**: Good file testing requires user interaction (ESC key) for optimal results. Future versions will automate this process.

## Usage

### 1. Compile the Tester
```bash
cd tester
make
```

### 2. Run the Tests
From the main cub3D directory:
```bash
./tester/cube_tester
```

Or from the tester directory:
```bash
cd tester
./cube_tester
```

### 3. During Good File Tests
- Watch for the game window to appear
- Press **ESC** within 3 seconds when prompted
- The tester will capture the exit message and continue

## Example Output

```
cub3D Automatic Tester
======================

================================
  TESTING BAD FILES (Should show errors)
================================
Found 16 bad test files

✓ PASS - Error correctly detected: missing_north_texture.cub
✓ PASS - Error correctly detected: wrong_extension.txt
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

- **"./cub3D executable not found"**: Compile your main project first with `make`
- **No error messages detected**: Ensure your program outputs `"Error:\n"` exactly
- **Good file tests fail**: Check that your program outputs the required confirmation messages
- **Window doesn't appear**: Verify you have a working X11 display environment
- **ESC not working**: Try clicking the game window first, then press ESC

## Known Limitations (Alpha Version)

- ⚠️ Requires manual ESC key press for good file tests
- ⚠️ Basic timeout handling (may be inconclusive in some cases)
- ⚠️ Limited error message format checking
- ⚠️ No advanced validation of game mechanics

## Future Updates

- 🔄 Automatic ESC key simulation
- 🔄 Better error message validation
- 🔄 Program input validation
- 🔄 Memory leak detection

## Compilation

```bash
make        # Compile the tester
make clean  # Remove object files
make fclean # Remove executable and clean
make re     # Full recompilation
```

---

**Version**: Alpha 0.1
**Status**: Basic functionality testing only
**Next Update**: Improved automation and additional test cases
