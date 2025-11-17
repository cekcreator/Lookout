## Makefile for Lookout
## Builds using CMake and Cinder automatically
#
#BUILD_DIR := build
#EXECUTABLE := Lookout
#
#all:
#	mkdir -p $(BUILD_DIR)
#	cd $(BUILD_DIR) && cmake ..
#	cd $(BUILD_DIR) && $(MAKE) -j4
#
#run:
#	./$(BUILD_DIR)/$(EXECUTABLE)
#
#clean:
#	rm -rf $(BUILD_DIR)
# Makefile for Lookout

BUILD_DIR = build
TARGET = Lookout
CINDER_DIR = external/Cinder

all: $(CINDER_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(BUILD_DIR) --config Release

$(CINDER_DIR):
	@echo "Cinder not found. Initializing submodule..."
	@git submodule update --init --recursive

run: all
	@$(BUILD_DIR)/Release/$(TARGET) || $(BUILD_DIR)/$(TARGET)

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all run clean