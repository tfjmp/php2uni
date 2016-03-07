# PHP2Uni

This project build uppon the [IncludeOS](http://www.includeos.org/) and [Rump Kernel](http://rumpkernel.org/) Unikernel.
The idea is simply to transpile PHP file into a Unikernel.

In order to run it requires **Ubuntu 14.04 LTS x86_64**, either on physical or virtual machine.
For more configuration details please refer to [IncludeOS github page](https://github.com/hioa-cs/IncludeOS) and [Rumprun github page](https://github.com/rumpkernel/rumprun).
To get started simply:

```
  $ git clone https://github.com/tfjmp/php2uni.git
  $ cd php2uni
  $ make install
  $ make rump_test # test rump installation
  $ make all
  # bridge and run IncludeOS VM
  $ make bridge_includeos
  $ make run_includeos
   bridge and run Rump VM
  $ make bridge_rump
  $ make run_rump
```

The install phase may take a while (around 30mins) and will ask for root privileges.
However it needs to be executed only once. The make all command will generate a IncludeOS and a Rump Kernel image that run on qemu/KVM.

To modify the site create/edit PHP files in seed and modify in consequence the routes file.
At the moment very small subset of PHP is supported and type annotation is required.
Better support and a proper parser will come next!
