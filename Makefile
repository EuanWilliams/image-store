run:
	./build/image_store $(args)

build_unix:
	./scripts/build_unix.sh

build_win:
	sh ./scripts/build_win.sh

build_run: build_unix run
