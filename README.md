* Trying kernel mode hook
  - make -f Kbuild
  - test
    insmod nfhook
	(Packet info will be seen in /var/log/kern.log)

* Trying user mode hook
  - make
  - test
    sudo modprobe nfnetlink_queue
    sudo iptables -A INPUT -i enp0s8 -p icmp -j NFQUEUE --queue-num 0
    sudo ./nfqnl_test
	(Ping this host and the packets will be dropped)
    sudo iptables -D INPUT -i enp0s8 -p icmp -j NFQUEUE --queue-num 0

