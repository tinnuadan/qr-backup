# QR Backup

The idea of this project was taken from sunknudsen/qr-backup.

See https://github.com/sunknudsen/qr-backup for the purpose of this project.

This implementation is C++ as it allows a low-level access to the hardware. It will display the generatored QR Code without the need of a desktop environment.

## Build
This project was designed to run on a Raspberry Pi, so a linux environment is assumed.

### Install Prequisites 
```
$ apt install build-essential cmake libqrcodegencpp-dev git
```

### Clone the repository
```
$ git clone https://github.com/tinnuadan/qr-backup.git
```
## Build the code
```
$ cd qr-backup
$ mkdir build
$ cd build
$ cmake ../
$ make
```
## Proof of concept
```
$ echo "essence wisdom demise insane vital kitchen pet swarm robust warfare innocent dolphin" |\
 gpg --s2k-mode 3 --s2k-count 65011712 --s2k-digest-algo sha512 --cipher-algo AES256 --symmetric --armor |\
 ./qr-backup
```
### Note
The pgp documentation states that you should add
```
GPG_TTY=$(tty)
export GPG_TTY
```
to your `~/.bashrc` which is especially important if you run gpg on a PC without a window manager