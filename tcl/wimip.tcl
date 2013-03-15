#! /usr/bin/tclsh

set CheckIp(host) {checkip.dyndns.org}
set CheckIp(resource) {/}
set CheckIp(port) {http}
set CheckIp(myIp) {127.0.0.1}
set CheckIp(done) 0

proc sendHttpGetRequest { chan host resource } { 
   puts $chan "GET $resource HTTP/1.1"
   #puts $chan "From: bks62464@yahoo.com"
   puts $chan "User-agent: Mozilla/5.0"
   puts $chan "Connection: close"
   puts $chan "Host: $host"
   puts $chan ""
}

proc receiveHttpReply { chan } {
   global CheckIp
   if { [eof $chan] || [catch {gets $chan reply}] } {
      close $chan
      set CheckIp(done) 1
   } else {
      # interesting debug info
      puts "$reply" 
      set matches [regexp -nocase -expanded  {([\d]+[\.][\d]+[\.][\d]+[\.][\d]+)}  $reply where addr]
      if { 0 < $matches } { 
         set CheckIp(myIp)  "$addr" 
      }
   }
}

proc checkIp { } {
   global CheckIp
   set sock [socket -async $CheckIp(host) $CheckIp(port)]
   fconfigure $sock -blocking 0 -buffering line
   fileevent $sock readable [list receiveHttpReply $sock]
   fileevent $sock writable [list sendHttpGetRequest $sock $CheckIp(host) $CheckIp(resource)]

   after 5000 set CheckIp(done) 1
   vwait CheckIp(done)
   return $CheckIp(myIp)
}

set timestamp [clock format [clock seconds] -format {%d-%b-%Y %H:%M:%S}]
puts stdout "$timestamp [checkIp]"
