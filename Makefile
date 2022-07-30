.PHONY: build install amalgamate clean test doc-plain doc-mcss

BUILD_DIR ?= build
CSS_DIR   ?= ../doxygen-awesome-css

build: dependencies/zycore/CMakeLists.txt
	@if ! command -v cmake &> /dev/null; then \
		echo >&2 "ERROR: cmake is not installed. Please install it first."; \
	fi
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make -j$(nproc)

install: build
	cd $(BUILD_DIR) && make install

amalgamate:
	assets/amalgamate.py

clean:
	rm -rf $(BUILD_DIR)
	rm -rf doc
	rm -rf amalgamated-dist

test: build
	cd tests && ./regression.py test ../build/ZydisInfo
	cd tests && ./regression_encoder.py ../build/ZydisFuzz{ReEncoding,Encoder}

doc-plain:
	doxygen

doc-themed:
	@if [ ! -d "$(CSS_DIR)" ]; then \
		git clone https://github.com/jothepro/doxygen-awesome-css.git $(CSS_DIR); \
	fi

	doxygen Doxyfile-themed

dependencies/zycore/CMakeLists.txt:
	@if ! command -v git &> /dev/null; then \
		echo >&2 -n "ERROR: git is not installed. Please either manually place all"; \
		echo >&2    "dependencies in their respective paths or install git first."; \
		exit 1; \
	fi
	git submodule update --init --recursive
