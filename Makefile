install:
	mkdir -p build
	sudo apt-get install build-essential nasm texinfo clang-3.6 cmake ninja-build subversion zlib1g-dev libtinfo-dev
	sudo apt-get install ruby
	sudo apt-get install libc++-dev
	cd ./build && git clone https://github.com/tfjmp/php2cpp.git
	cd ./build/php2cpp && make install && make all
	cd ./build && git clone https://github.com/hioa-cs/IncludeOS.git
	cd ./build/IncludeOS && ./install.sh
	cd ./build && git clone http://repo.rumpkernel.org/rumprun
	cd ./build/rumprun && git submodule update --init
	cd ./build/rumprun && git submodule update --init
	cd ./build/rumprun && CC=cc ./build-rr.sh hw
	export PATH="${PATH}:${PWD}/build/rumprun/rumprun/bin"

rump_test:
	cd ./test && x86_64-rumprun-netbsd-gcc -o helloer-rumprun helloer.c
	cd ./test && rumprun-bake hw_virtio helloer-rumprun.bin helloer-rumprun
	cd ./test && rumprun kvm -i helloer-rumprun.bin

all:
	cp -r ./seed ./build
	cp -r ./src/http/* ./build/seed
	cp -r ./src/php/* ./build/seed
	cp -r ./src/IncludeOS/* ./build/seed
	cp -r ./src/rump/* ./build/seed
	./build.rb ./build/seed/routes
	cd ./build/seed && make
	cp ./build/seed/PHP2Uni.img ./seed/php2uni-includeos.img
	cd ./build/seed && clang++-3.6 -std=c++11 -stdlib=libc++ rump.cpp -o app.o -pedantic -Wall
	cp ./build/seed/app.o ./seed/app.o
	cd ./build/seed && x86_64-rumprun-netbsd-g++ -o php2uni-rumprun rump.cpp
	cd ./build/seed && rumprun-bake hw_virtio php2uni-rumprun.img php2uni-rumprun
	cp ./build/seed/php2uni-rumprun.img ./seed/php2uni-rumprun.img

clean:
	rm -r ./build/seed/*

run:
	./seed/run.sh ./seed/php2uni-includeos.img

tap_rump:
	sudo ip tuntap add tap0 mode tap
	sudo ip addr add 10.0.120.100/24 dev tap0
	sudo ip link set dev tap0 up

run_rump:
	cd ./seed && rumprun kvm -i -M 128 -I if,vioif,'-net tap,script=no,ifname=tap0' -W if,inet,static,10.0.120.101/24 -- ./php2uni-rumprun.img


default: all
