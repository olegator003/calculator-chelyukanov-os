# Tools
CC  ?= gcc
CXX ?= g++
AR  ?= ar

# Directories
SRC_DIR   ?= src
TESTS_DIR ?= tests/unit
BUILD_DIR ?= build
GTEST_DIR ?= googletest/googletest

APP_BUILD_DIR=$(BUILD_DIR)/app
TEST_BUILD_DIR=$(BUILD_DIR)/test

# Flags
CFLAGS   += -g -Wall -Wextra -Wpedantic -Werror -std=c11
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

# Sources
APP_SRCS := $(shell find $(SRC_DIR) -name 'main.c')
TEST_SRCS := $(shell find $(TESTS_DIR) -name '*.cpp')

# Objects
APP_OBJS := $(patsubst $(SRC_DIR)/%.c, $(APP_BUILD_DIR)/%.o, $(APP_SRCS))
TEST_OBJS := $(patsubst $(SRC_DIR)/%.c, $(TEST_BUILD_DIR)/app/%.o, $(APP_SRCS))
UNIT_TESTS_OBJS := $(patsubst $(TESTS_DIR)/%.cpp, $(TEST_BUILD_DIR)/unit-tests/%.o, $(TEST_SRCS))

# Create necessary directories
$(shell mkdir -p $(APP_BUILD_DIR) $(TEST_BUILD_DIR)/app $(TEST_BUILD_DIR)/unit-tests)

################
# MAIN TARGETS #
################

all: $(BUILD_DIR)/app.exe $(BUILD_DIR)/unit-tests.exe

clean:
	rm -rf $(BUILD_DIR)

run-int: $(BUILD_DIR)/app.exe
	@$<

run-float: $(BUILD_DIR)/app.exe
	@$< --float

run-unit-test: $(BUILD_DIR)/unit-tests.exe
	@$<

#############
# BUILD APP #
#############

-include $(APP_OBJS:.o=.d)
$(APP_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/app.exe: $(APP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

###############
# BUILD TESTS #
###############

-include $(TEST_OBJS:.o=.d)
$(TEST_BUILD_DIR)/app/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -DGTEST -c $< -o $@

-include $(UNIT_TESTS_OBJS:.o=.d)
$(TEST_BUILD_DIR)/unit-tests/%.o: $(TESTS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/unit-tests.exe: $(TEST_OBJS) $(UNIT_TESTS_OBJS) $(TEST_BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

####################################
# BUILD GOOGLE TEST STATIC LIBRARY #
####################################

$(TEST_BUILD_DIR)/gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc $(GTEST_DIR)/src/*.h $(GTEST_DIR)/include/gtest/*.h
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/gtest_main.o: $(GTEST_DIR)/src/gtest_main.cc $(GTEST_DIR)/src/*.h $(GTEST_DIR)/include/gtest/*.h
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/gtest_main.a: $(TEST_BUILD_DIR)/gtest-all.o $(TEST_BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

###############
# INTEGRATION #
###############

venv:
	python3 -m venv venv && source venv/bin/activate && pip install pytest

run-integration-tests:
	source venv/bin/activate && pytest tests/integration
