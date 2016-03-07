#!/bin/bash

### TODO: check that we're running as vagrant user and not root

cd
sudo apt-get update -y
sudo apt-get update -y
sudo apt-get install -y build-essential git subversion

### TODO: don't re-run install if it's been done already

# Install steps from Makefile (needs modification for VM use)

mkdir -p build
# set up SSH deployment key
[ -e ~/.ssh/php2cpp-deploy ] || { cp /vagrant/onVagrantVM/php2cpp-deploy ~/.ssh/php2cpp-deploy; chmod 600 ~/.ssh/php2cpp-deploy; }
[ -e ~/.ssh/ssh-config ] || cp /vagrant/onVagrantVM/ssh-config-template ~/.ssh/config

# work around Subversion HTTP download glitch
# create ~/.subversion if not already there
svn status /dev/null 2>/dev/null
# TODO improve this configuration modification
SVN_ADD_CONFIG='http-chunked-requests = no'
grep -q "$SVN_ADD_CONFIG"  ~/.subversion/servers || echo "$SVN_ADD_CONFIG" >>~/.subversion/servers
cd ~/build && git clone getphp2cpp:tfjmp/php2cpp.git
cd ~/build/php2cpp && make install && make all
cd ~/build && git clone https://github.com/hioa-cs/IncludeOS.git
cd ~/build/IncludeOS && ./install.sh
cd ~/build && git clone http://repo.rumpkernel.org/rumprun
cd ~/build/rumprun && git submodule update --init
cd ~/build/rumprun && git submodule update --init
cd ~/build/rumprun && CC=cc ./build-rr.sh hw
export PATH="${PATH}:${PWD}/build/rumprun/rumprun/bin"
echo "export PATH=\"\${PATH}:${PWD}/build/rumprun/rumprun/bin\"" | sudo tee /etc/profile.d/rumprun.sh
sudo chmod +x /etc/profile.d/rumprun.sh

# copy files to ensure that Makefile works
cd /vagrant
cp -r seed src build.rb Makefile ~

# do everytime build steps
cd
make all
make run_includeos
make run_rump
