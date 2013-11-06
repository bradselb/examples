#! /usr/bin/tclsh

package require base64

set host {}
set port {}
set resource {}

set username {}
set password {}
set auth [base64::encode $username:$password]

set done 0

# --------------------------------------------------------------------------
proc sendRequest { chan } { 
   global host
   global resource
   global auth
   puts $chan "GET /$resource HTTP/1.0"
   puts $chan "Host: $host"
   #puts $chan "Connection: close"
   puts $chan "User-agent: a Tcl script"
   puts $chan "Authorization: Basic $auth"
   puts $chan ""
}

# --------------------------------------------------------------------------
proc getReply { chan } {
   global done
   set total 0
   while { ! $done } {
      set count [gets $chan reply]
      if { [eof $chan] } {
         puts stdout "\nread $total characters from socket\n\n" 
         close $chan
         set done 1
         break
      }
      if { $count > 0 } { 
         set total [expr {$total + $count}]
         puts stdout "$reply"
      }
   }
}


# --------------------------------------------------------------------------
set sock [socket -async $host $port]
fconfigure $sock -blocking 0
fileevent $sock readable [list getReply $sock]
fileevent $sock writable [list sendRequest $sock]

after 10000 set done 1
vwait done
