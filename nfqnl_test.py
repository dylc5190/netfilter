import os,sys,nfqueue,socket
from scapy.all import *

def process(i, payload):
  data = payload.get_data()
  pkt = IP(data)

  # Check if TCP flags is ACK|PSH
  if pkt[IP].proto == 1:
      # Dropping the packet
      pkt[ICMP].load = str(pkt[ICMP].load).replace("bcd","234")
      del pkt[IP].chksum
      del pkt[ICMP].chksum
      payload.set_verdict_modified(nfqueue.NF_ACCEPT, str(pkt), len(pkt))
  else:
      # Accepting the packet
      payload.set_verdict(nfqueue.NF_ACCEPT)
  
def main():
  q = nfqueue.queue()
  q.open()
  q.unbind(socket.AF_INET)
  q.bind(socket.AF_INET)
  q.set_callback(process)
  q.create_queue(0)

  try:
      q.try_run()
  except KeyboardInterrupt:
      print "Exiting..."
      q.unbind(socket.AF_INET)
      q.close()
      sys.exit(1)

main()

