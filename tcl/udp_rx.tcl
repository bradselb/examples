#! /usr/bin/tclsh 

package require udp
set port {9}

proc logPacket {host_info msg} {
   set timestamp [clock format [clock seconds] -format {%d.%m.%Y %H:%M:%S}]
   set f [open "ReceivedUdpMessage.log" a]
   puts  "$timestamp $host_info $msg"
   puts $f "$timestamp $host_info $msg"
   close $f
}

proc handleUdpMessage {sock} {
   global t
   set packet [read $sock]
   set peer [fconfigure $sock -peer]
   logPacket $peer $packet
   if { [string compare -nocase $packet {quit}] == 0 } {
      set ::t 1
   }
}

proc udp_listen {port} {
   set sock [udp_open $port]
   fconfigure $sock -buffering none -translation binary
   fileevent $sock readable [list ::handleUdpMessage $sock]
   puts "Listening on udp port: [fconfigure $sock -myport]"
   return $sock
}


set t 0
# after 10000 [list set t 1]
set sock [udp_listen $port]
vwait t
close $sock


