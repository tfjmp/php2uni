# php2uni

This project build uppon the [IncludeOS](http://www.includeos.org/) Unikernel.
The idea is simply to transpile PHP file into a Unikernel.

In order to run it requires **Ubuntu 14.04 LTS x86_64**, either on physical or virtual machine.
For more configuration details please refer to [IncludeOS github page](https://github.com/hioa-cs/IncludeOS).
To get started simply:

```
  $ make install
  $ make all
```

The install phase may take a while (around 30mins) and will ask for root privileges.
However it needs to be executed only once.

To modify the site create/edit PHP files in seed and modify in consequence the routes file.
At the moment very small subset of PHP is supported and type annotation is required.
Better support and a proper parser will come next!
