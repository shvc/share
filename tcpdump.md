### tcpdump http headers
- Commands
```
tcpdump -AnS -s 0 'tcp port 80' | grep -B3 -A10 "Server"

tcpdump -AnS -s 0 'tcp host 172.16.3.24 and port 9020'

tcpdump -AnS -s 10240 'tcp port 20090 and (((ip[2:2] - ((ip[0]&0xf)<<2)) - ((tcp[12]&0xf0)>>2)) != 0)' | egrep --line-buffered "^........(GET |HTTP\/|POST |HEAD )|^[A-Za-z0-9-]+: " | sed -r 's/^........(GET |HTTP\/|POST |HEAD )/\n\1/g'

tcpdump -AnS -s 10240 'tcp port 20090' | grep -v IP | egrep --line-buffered "..(GET |\.HTTP\/|POST |HEAD )|^[A-Za-z0-9-]+: " |sed -r 's/..(GET |HTTP\/|POST |HEAD )/\n\n\1/g'

# capture local machine package(dst 172.16.3.98 and src 172.16.3.98)
tcpdump -AnSs 0  -i any 'host 172.16.3.98'
```

- Usage
```
-A    Print each packet (minus its link level header) in ASCII.
-n    Don't convert host addresses to names.  This can be used to avoid DNS lookups.
-S    (--absolute-tcp-sequence-numbers)
      Print absolute, rather than relative, TCP sequence numbers.
-s snaplen(--snapshot-length=snaplen)
      Snarf  snaplen bytes of data from each packet rather than the default of 262144 bytes.  Packets truncated because
      of a limited snapshot are indicated in the output with ``[|proto]'', where proto is  the  name  of  the  protocol
      level  at which the truncation has occurred.  Note that taking larger snapshots both increases the amount of time
      it takes to process packets and, effectively, decreases the amount of packet buffering.  This may  cause  packets
      to  be  lost.   You should limit snaplen to the smallest number that will capture the protocol information you're
      interested in.  Setting snaplen to 0 sets it to the default of 262144, for backwards  compatibility  with  recent
      older versions of tcpdump.
```
