# cat /usr/local/sbin/service-close
#!/bin/sh
if test $# -eq 0; then
        echo usage: $( basename $0 ) service ... 1>&2
        exit 1
fi
while test $# -ne 0; do
        /usr/sbin/iptables -D INPUT -p tcp --dport "$1" -j ACCEPT
        /usr/sbin/iptables -D INPUT -p udp --dport "$1" -j ACCEPT
        shift
done
