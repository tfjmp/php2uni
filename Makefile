install:
	mkdir -p build
	sudo apt-get install build-essential nasm texinfo clang-3.6 cmake ninja-build subversion zlib1g-dev libtinfo-dev
	sudo apt-get install ruby
	cd ./build && git clone https://github.com/tfjmp/php2cpp.git
	cd ./build/php2cpp && make install && make all
	cd ./build && git clone https://github.com/hioa-cs/IncludeOS.git
	cd ./build/IncludeOS && ./install.sh

all:
	cp -r ./seed ./build
	cp -r ./src/http/* ./build/seed
	cp -r ./src/php/* ./build/seed
	cp -r ./src/IncludeOS/* ./build/seed
	cp -r ./src/rump/* ./build/seed
	./build.rb ./build/seed/routes
	cd ./build/seed && make
	cp ./build/seed/PHP2Uni ./seed/PHP2Uni
	cp ./build/seed/PHP2Uni.img ./seed/PHP2Uni.img
	cd ./build/seed && clang++-3.6 -std=c++11 -stdlib=libc++ rump.cpp -o app.o -pedantic -Wall
	cp ./build/seed/app.o ./seed/app.o
	rm -r ./build/seed/*

run:
	./seed/run.sh ./seed/PHP2Uni.img

default: all
