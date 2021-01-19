# FlappyTiger
The flappybird clone you definately dont need. This is my first game written in C++ using glfw.

## Installing (Linux)
Arch:
AUR package available as `flappytiger` at https://aur.archlinux.org/packages/flappytiger/
````
git clone https://aur.archlinux.org/flappytiger.git
cd flappytiger
makepkg -si
````
Other:
```
git clone https://github.com/Tigermouthbear/flappytiger.git
cd flappytiger
git submodule update --init --recursive
mkdir build && cd build
cmake -DINSTALL_APP=ON ..
make
sudo make install
```