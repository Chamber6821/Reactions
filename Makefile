
include configuration.mk # user configuration for user platform

MODE ?= Debug
PERMISSIBLE_MODS=Debug Release
ifeq ($(filter $(MODE), $(PERMISSIBLE_MODS)),)
$(warning "Mode '$(MODE)' is not permissible!")
$(warning "Permissible mods: $(PERMISSIBLE_MODS)")
$(warning "Use 'make <target> MODE=Debug' or 'make <target> MODE=Release' to fix")
$(error "Mode '$(MODE)' is not permissible!")
endif
MODE_LOWER = $(subst Debug,debug,$(subst Release,release,$(MODE)))
$(MODE) = ON

TESTS_TARGET = tests

BUILD_DIR = $(BUILD_DIR_PREFIX)$(MODE_LOWER)
CACHE_DIR = $(BUILD_DIR)/make-cache
TESTS_EXECUTABLE = "$(BUILD_DIR)/$(TESTS_TARGET)/$(TESTS_TARGET)"

HEADERS = $(wildcard src/**/*.h)
SOURCES = $(wildcard src/**/*.cpp tests/**/*.cpp)
CODES   = $(HEADERS) $(SOURCES)
CONFIGS = $(wildcard CMakeLists.txt **/CMakeLists.txt)

CLANG_FORMAT_CACHE_FOLDER = $(CACHE_DIR)/clang-format
CLANG_FORMAT_CACHE_FILES = $(foreach x,$(CODES),$(CLANG_FORMAT_CACHE_FOLDER)/$(x).label)

.PHONY: validate cmake tests format clean
all: validate

validate: format tests
tests: cmake $(CACHE_DIR)/tests
format: cmake $(CLANG_FORMAT_CACHE_FILES)
cmake: $(BUILD_DIR)

clean:
	cmake -D PATH:STRING=$(BUILD_DIR) -P ./cmake/rm.cmake

$(BUILD_DIR): $(CONFIGS) $(SOURCES) .clang-tidy
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(MODE) $(CMAKE_OPTIONS)

$(CACHE_DIR):
	cmake -D PATH:STRING=$(CACHE_DIR) -P ./cmake/mkdir-p.cmake

$(CACHE_DIR)/tests: $(BUILD_DIR) $(CODES) $(CACHE_DIR)
	cmake --build $(BUILD_DIR) -t $(TESTS_TARGET) $(CMAKE_BUILD_OPTIONS)
	$(TESTS_EXECUTABLE) --order-by=rand
	echo "" > $(CACHE_DIR)/tests

$(CLANG_FORMAT_CACHE_FILES): $(CLANG_FORMAT_CACHE_FOLDER)/%.label: % .clang-format
	cmake -D PATH:STRING=$(dir $@) -P ./cmake/mkdir-p.cmake
	clang-format -i $<
	echo "" > $@
