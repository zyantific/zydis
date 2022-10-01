.PHONY: build configure install amalgamate clean test doc doc-plain doc-themed

BUILD_DIR ?= build
CSS_DIR   ?= ../doxygen-awesome-css

build: configure
	cmake --build $(BUILD_DIR) -j$(nproc)

configure: dependencies/zycore/CMakeLists.txt
	@if ! command -v cmake > /dev/null; then \
		echo >&2 "ERROR: cmake is not installed. Please install it first."; \
	fi
	cmake -B $(BUILD_DIR)

install: build
	cmake --install $(BUILD_DIR)

amalgamate:
	assets/amalgamate.py

clean:
	rm -rf $(BUILD_DIR)
	rm -rf doc
	rm -rf amalgamated-dist

test: build
	cd tests && ./regression.py test ../build/ZydisInfo
	cd tests && ./regression_encoder.py ../build/ZydisFuzz{ReEncoding,Encoder}

doc: configure
	cmake --build $(BUILD_DIR) --target doc

doc-plain:
	rm -rf "$(CSS_DIR)"
	$(MAKE) doc

doc-themed:
	@if [ ! -d "$(CSS_DIR)" ]; then \
		git clone --depth 1 https://github.com/jothepro/doxygen-awesome-css.git $(CSS_DIR); \
	fi
	$(MAKE) doc

dependencies/zycore/CMakeLists.txt:
	@if ! command -v git > /dev/null; then \
		echo >&2 -n "ERROR: git is not installed. Please either manually place all"; \
		echo >&2    "dependencies in their respective paths or install git first."; \
		exit 1; \
	fi
	git submodule update --init --recursive
