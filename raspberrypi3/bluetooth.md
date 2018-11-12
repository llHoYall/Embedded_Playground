# RaspberryPi 3 Bluetooth

## Bluetooth Installation

### Remove Default Bluetooth Stack

```sh
$ sudo apt-get --purge remove bluez
```

### Download

`http://www.bluez.org/download`

```sh
$ wget http://www.kernel.org/pub/linux/bluetooth/bluez-5.44.tar.xz
```

### Installation

```sh
$ tar xvf bluez-5.44.tar.xz
$ cd bluez-5.44
$ sudo apt-get update
$ sudo apt-get install -y libusb-dev libdbus-1-dev libglib2.0-dev libudev-dev libical-dev libreadline-dev
$ ./configure
$ make
$ sudo make install
```

### Bluetooth Start/Stop/Enable/Disable Service

```sh
$ sudo systemctl daemon-reload
$ sudo systemctl start bluetooth
$ sudo systemctl stop bluetooth
$ systemctl status bluetooth
$ sudo systemctl enable bluetooth
$ sudo systemctl disable bluetooth
```

### Enable BLE Feature

```sh
$ sudo vi /lib/systemd/system/bluetooth.service
> ExecStart=/usr/local/libexec/bluetooth/bluetoothd --experimental
$ sudo systemctl daemon-reload
$ sudo systemctl restart bluetooth
```

### Install pyBluez

```sh
$ sudo apt-get install libbluetooth-dev
$ sudo apt-get install libboost-python-dev
$ sudo pip install gattlib
$ sudo pip3 install gattlib
$ sudo pip install pybluez
$ sudo pip3 install pybluez
```

## Bluetooth Control

블루투스 제어 프로그램 실행.

```sh
$ sudo bluetoothctl
```

자주 사용하는 명령어는 아래와 같다.

* `help`
* `show`
* `devices`
* `paired-devices`
* `power <on/off>`
* `pairable <on/off>`
* `discoverable <on/off>`
* `agent <on/off/capability>`
* `default-agent`
* `scan <on/off>`
* `pair xx:xx:xx:xx:xx:xx`
* `info xx:xx:xx:xx:xx:xx`
* `connect xx:xx:xx:xx:xx:xx`
* `disconnect xx:xx:xx:xx:xx:xx`

HCI를 사용하여 블루투스를 제어한다.

```sh
$ sudo hciconfig
```

> Ex) $ sudo hciconfig -i hci0 \<cmd\> \<data\>
