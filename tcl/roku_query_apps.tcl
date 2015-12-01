#!/usr/bin/tclsh

package require udp

set addr {192.168.117.124}
set port {8060}
set done {0}

proc send {sock} {
    global addr
    global port
    puts -nonewline $sock "GET /query/apps HTTP/1.1\r\n"
    puts -nonewline $sock "Host: $addr:$port\r\n"
    puts -nonewline $sock "User-Agent: myscript\r\n"
    puts -nonewline $sock "Accept */*\r\n"
    puts -nonewline $sock "\r\n"
#    puts $sock 
}


proc rcv {sock} {
    global done
    set reply [read $sock]
    puts "$reply"
    set done 1
}


set sock [socket $addr $port]
fconfigure $sock -buffering line -translation binary
::send $sock
fileevent $sock readable [list ::rcv $sock]

vwait done

puts "done"
close $sock

