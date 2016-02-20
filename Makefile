install:
	mkdir -p build
	cd ./build && git clone https://github.com/tfjmp/php2cpp.git
	cd ./build/php2cpp && make install && make all
	cd ./build && git clone https://github.com/hioa-cs/IncludeOS.git
	cd ./build/IncludeOS && ./install.sh

all:
	cp -r ./seed ./build
	cp -r ./src/http/* ./build/seed
	cp -r ./src/php/* ./build/seed
	./build.rb ./build/seed/routes
	cd ./build/seed && make
	cp ./build/seed/PHP2Uni ./seed/PHP2Uni
	cp ./build/seed/PHP2Uni.img ./seed/PHP2Uni.img

run:
	./seed/run.sh ./seed/PHP2Uni.img

default: all
