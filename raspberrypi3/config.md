# RaspberryPi 3 Configuration

## OS Installation

### Download Image

`https://www.raspberrypi.org/downloads`

### Install Image

* MAC / Linux

microSD mount 확인.

> $ diskutil list

> $ sudo diskutil unmountDisk /dev/disk#

microSD에 OS 설치.

> $ sudo dd bs=1m if=xxx.img of=/dev/disk#

* Windows

`https://sourceforge.net/projects/win32diskimager`

## Configuration

기본 계정은 다음과 같다.
* ID: pi
* PW: raspberry

### root 계정 활성화

> $ sudo passwd root


### Raspberry Pi configuration

> $ sudo raspi-config

Note. 버전마다 메뉴의 위치가 다르다.

```
Expand Filesystem
Change User Password
SSH
Keyboard
```

### Internet configuration

* ethernet

> $ sudo vi /etc/network/interfaces

```sh
iface lo inet loopback
iface eth0 inet dhcp
```

> $ sudo /etc/init.d/networking restart

* Wi-Fi

> $ sudo vi /etc/network/interfaces

```sh
iface wlan0 inet dhcp
```

> $ sudo vi /etc/wpa_supplicant/wpa_supplicant.conf

```sh
network={
	ssid="SSID"
	psk="PASSWORD"
}
```

> $ sudo ifdown wlan0
>
> $ sudo ifup wlan0

### RaspberryPi update & upgrade

> $ sudo apt-get update
>
> $ sudo apt-get upgrade -y
>
> $ sudo apt-get dist-upgrade -y
>
> $ sudo rpi-update
