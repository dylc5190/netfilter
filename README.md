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

* Trying user mode hook with Python script
  - setup
    sudo apt-get install nfqueue-bindings-python
	install scapy (optional. only if you need it in your Python script as this example.)
  - test
    sudo python nfqnl_test.py
	(Ping this host from a Windows machine and you can see the message "MISCOMPARE at offset 1" because the payload has been modified)
