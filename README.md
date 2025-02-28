# calculator-knyazev-rv

## What Has Been Done?
### Implementation
- **Arithmetic Calculator** supporting:
  - Integer mode (`/` rounds toward zero) and float mode (`--float` flag)
  - Parentheses `()`, operators `+`, `-`, `*`, `/`
  - Input validation: allowed chars `[0-9()*+/\-.\s]`
  - Error handling: invalid syntax, division by near-zero values (<1e-4)
- **Unit Tests** using GoogleTest framework
- **Build System**: Makefile with targets for app, tests, and clean
- **Code Style**: `.clang-format` based on WebKit

---

## How to Run/Use It?
### Build & Run
```bash
# Build everything
make all

# Integer mode (default)
echo "(2+3)*4" | make run-int      # Output: 20

# Float mode
echo "10/3" | make run-float       # Output: 3.3333

# Run tests
make run-unit-test

# Clean artifacts
make clean
```
---

##How It's Made?
### Project structure
```bash
src/
  main.c          
  calculator.h    
  calculator.c    
tests/unit/
  tests.cpp       
Makefile          
.clang-format
.gitignore
```
---

## Building on your machine

To build this program You need a **C compiler** gcc.  


You'll also need `git`, `cmake` and `make` if you want to run unit tests

All sources are in `src/` folder so you can compile them yourself or use **Makefile**

### Makefile
```bash
make all            # to build program (app.exe) and unit tests (unit-tests.exe)
make clean          # to clean build artifacts
make run-int        # to run app.exe
make run-float      # to run app.exe --float
make run-unit-test  # to run unit-tests.exe
```

##Key Components

###Parser Architecture:

Recursive descent with 3 levels: add_subt → mult_div → num

State encapsulation in CalculatorState struct

###Error Handling:

Global error flag with early exit

Input validation via strchr whitelist

###Tests:

5 test cases covering operations, modes, and error detection

Input mocking via temporary files

