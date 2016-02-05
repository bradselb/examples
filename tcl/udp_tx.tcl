#! /usr/bin/tclsh

package require udp

set host_ip {localhost}
set port {9}

# Send data to a remote UDP socket
proc udp_puts {host port msg} {
    set s [udp_open]
    fconfigure $s -remote [list $host $port]
    puts -nonewline $s "$msg"
    close $s
}

set msg_list [list hello fish eat flies and frogs do too good-bye quit]
foreach msg $msg_list { 
   set timestamp [clock format [clock seconds] -format {%d.%m.%Y %H:%M:%S}]
   puts "$timestamp  $host_ip:$port   $msg"
   udp_puts $host_ip $port $msg
   after 1000 
}

