# Makefile for Lookout
# Builds using CMake and Cinder automatically

BUILD_DIR := build
EXECUTABLE := Lookout

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && $(MAKE) -j4

run:
	./$(BUILD_DIR)/$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)
