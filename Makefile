ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
LIB_DIR:=$(ROOT_DIR)/libkiibohd
KEYBOARD_DIR:=$(ROOT_DIR)/controller/Keyboards
BUILD_SCRIPT:=klltest.bash
BUILD_DIR:=$(KEYBOARD_DIR)/Testing/linux-gnu.klltest.gcc.ninja

.PHONY: build test all
all: build doc test

clean:
	rm -rf $(LIB_DIR)
	rm -rf $(BUILD_DIR)

controller/CMakeLists.txt:
	git submodule init
	git submodule update

$(LIB_DIR)/libkiibohd.so: controller/CMakeLists.txt
	rm -rf $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	sed -i 's/-DSANITIZER=1//;s/EnableSaniziter=true/EnableSaniziter=false/' $(KEYBOARD_DIR)/Testing/$(BUILD_SCRIPT)
	cd $(KEYBOARD_DIR); pipenv install
	cd $(KEYBOARD_DIR); pipenv run bash -c "cd Testing && ./$(BUILD_SCRIPT)"
	cp $(BUILD_DIR)/{*.h,*.so} $(LIB_DIR)

build: $(LIB_DIR)/libkiibohd.so
	cargo build

doc:
	cargo doc

test:
	cargo test -- --skip bindgen_test --test-threads 1 --nocapture
