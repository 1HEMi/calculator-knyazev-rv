CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11 -Isrc
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -Isrc
LDFLAGS = -lm
GTEST_FLAGS = -lgtest -lgtest_main -lpthread

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/calculator.c
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
TEST_SRC = tests/unit/tests.cpp

APP = app.exe
TEST_APP = unit-tests.exe

all: $(BUILD_DIR)/$(APP) $(BUILD_DIR)/$(TEST_APP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(APP): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(TEST_APP): $(TEST_SRC) $(OBJ_DIR)/calculator.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(GTEST_FLAGS)

run-int: $(BUILD_DIR)/$(APP)
	@echo "Running integer mode..."
	@./$(BUILD_DIR)/$(APP)

run-float: $(BUILD_DIR)/$(APP)
	@echo "Running float mode..."
	@./$(BUILD_DIR)/$(APP) --float

run-unit-test: $(BUILD_DIR)/$(TEST_APP)
	@echo "Running unit tests..."
	@./$(BUILD_DIR)/$(TEST_APP)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run-int run-float run-unit-test
