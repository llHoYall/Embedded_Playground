# RaspberryPi3 for WiFi AP

라즈베리파이3를 Wi-Fi AP로 사용하기 위한 방법이다.

> $ sudo raspi-config

Wi-Fi country를 Korea(South)로 선택한다.

재부팅을 물어보면 확인하여 재부팅한다.

> $ sudo apt-get install dnsmasq hostapd

> $ sudo vi /etc/dhcpcd.conf

맨 아래에 다음을 입력한다.

```sh
denyinterfaces wlan0
```

> $ sudo vi /etc/network/interfaces

다음과 같이 수정한다

```sh
allow-hotplug wlan0
iface wlan0 inet static
  address 172.24.1.1
  netmask 255.255.255.0
  network 172.24.1.0
  broadcast 172.24.1.255
# wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf
```

> $ sudo service dhcpcd restart

> $ sudo ifdown wlan0
>
> $ sudo ifup wlan0

> $ sudo vi /etc/hostapd/hostapd.conf

새로운 파일이 생성되면 다음의 내용을 입력한다.

```sh
interface=wlan0
driver=nl80211
ssid=hRPi3-AP
hw_mode=g
channel=6
ieee80211n=1
wmm_enabled=1
ht_capab=[HT40][SHORT-GI-20][DSSS_CCK-40]
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_key_mgmt=WPA-PSK
wpa_passphrase=rlawjdgh
rsn_pairwise=CCMP
```

> $ sudo /usr/sbin/hostapd /etc/hostapd/hostapd.conf

잘 동작한다면 `<CTRL-c>`를 입력하여 종료하고 동작하지 않으면, `ifdown-ifup`을 반복하자.

> $ sudo vi /etc/default/hostapd

다음과 같이 수정을 한다.

```sh
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```

> $ sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig

> $ sudo vi /etc/dnsmasq.conf

다음의 내용으로 파일을 만든다.

```
interface=wlan0
listen-address=172.24.1.1
bind-interfaces
server=8.8.8.8
domain-needed
bogus-priv
dhcp-range=172.24.1.50,172.24.1.150,12h
```

> $ sudo vi /etc/sysctl.conf

`#net.ipv4.ip_forward=1`의 주석을 제거한다.

> $ sudo sh -c "echo 1 > /proc/sys/net/ipv4/ip_forward"

> $ sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
>
> $ sudo iptables -A FORWARD -i eth0 -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
>
> $ sudo iptables -A FORWARD -i wlan0 eth0 -j ACCEPT
>
> $ sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"

> $ sudo vi /etc/rc.local

fi와 exit 0 사이에 다음의 내용을 추가한다.

```sh
iptables-restore < /etc/iptables.ipv4.nat
```

> $ sudo service hostapd start
>
> $ sudo service dnsmasq start
