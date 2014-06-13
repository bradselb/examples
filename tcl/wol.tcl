#!/usr/bin/tclsh
package require udp

# broadcast a 'magic packet' to wake the host whose 
# ethernet adapter has the specified  mac address 

set mac {00:11:22:33:44:55}
set addr {255.255.255.255}
set port {9}

set macbytes [split $mac {:-}]

set bytes [list]
for {set i 0} {$i < 16} {incr i} {
    lappend bytes {FF}
}

for {set i 0} {$i < 16} {incr i} {
    set bytes [concat $bytes $macbytes]
}

proc send {sock bytelist} { 
    puts "hello"
    puts $sock [binary format H* [join $bytelist ""]]
    flush $sock
}

set sock [udp_open]
fconfigure $sock -remote "$addr $port"
fconfigure $sock -translation binary -broadcast 1
::send $sock $bytes
close $sock

