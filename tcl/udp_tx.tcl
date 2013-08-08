#! /usr/bin/tclsh

package require udp

set host_ip {hostname.mydomain.tld}
set port {62464} 

# Send data to a remote UDP socket
proc udp_puts {host port msg} {
    set s [udp_open]
    fconfigure $s -remote [list $host $port]
    puts -nonewline $s "$msg"
    close $s
}

set msg_list [list hello fish eat flies and frogs do too good-bye]
set timestamp [clock format [clock seconds] -format {%d.%m.%Y %H:%M:%S}]
foreach msg $msg_list { 
   puts "$timestamp  $host_ip:$port   $msg"
   udp_puts $host_ip $port $msg
   after 1000 
}

