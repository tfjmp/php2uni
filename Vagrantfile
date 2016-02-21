# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.network "forwarded_port", guest: 80, host: 8080
  # could do... config.vm.network "private_network", ip: "192.168.33.10"

  config.vm.provider "virtualbox" do |vb|
    # add a bit more memory (2GiB)
    vb.customize ["modifyvm", :id, "--memory", "2048"]
    # TODO should probably provide multiple cores too
  end
#  config.vm.provision "shell", path: "onVagrantVM/setup-VM.sh"
  config.vm.provision "shell",
    inline: "/usr/bin/sudo -i -u vagrant /vagrant/onVagrantVM/setup-VM.sh"
end
