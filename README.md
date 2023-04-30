`lightdm-js` is a node native addon that lets you communicate with the LightDM daemon on your system without using `node-gtk`.
It does so using `node-addon-api` to circumvent the need for GIR. A downside to this approach is that it may be prone to breaking.

The code right now is barely tested, so for anyone reading this, be careful if you decide to use it in a LightDM greeter implementation.
# Usage
Todo

# Installation
As of now, there are no pre-built binaries available.
The addon relies on two headers, `lightdm.h` and `glib.h`.
For Arch, these two headers are installed with the following packages:
```
sudo pacman -S lightdm glib2
```