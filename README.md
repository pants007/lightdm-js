`lightdm-js` is a node native addon that lets you communicate with the LightDM daemon on your system without using `node-gtk`.
# Usage
Todo

# Installation
As of now, there are no pre-built binaries available.
The addon relies on two headers, `lightdm.h` and `glib.h`.
For Arch, these two headers are installed with the following packages:
```
sudo pacman -S lightdm glib2
```