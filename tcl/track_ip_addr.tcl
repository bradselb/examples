#! /usr/bin/tclsh

package require http

array set CheckIp {
    url {http://checkip.dyndns.org:8245}
    timeout 5000
}

set timestamp [clock format [clock seconds] -format {%d-%b-%Y %T}]
set path [file join / var tmp track_ip_addr.log]

if {![catch {open $path {r}} f]} {
    # successfully opened file for read.
    set last_line {}
    while {[gets $f line] > 0} {
        # only interested in last line.
        set last_line $line
    }
    close $f
    set prev_log_entry [split $last_line]
    set PrevState(addr) [lindex $prev_log_entry 2]
} elseif {![catch {open $path {w}} f]} {
    # cannot open for read but can open for write
    # assume that reason is file does not exist. 
    # and create one. 
    puts $f "$timestamp 0.0.0.0"
    close $f
    return
} else {
    # cannot open for read and  cannot open for write either
    # permissions? 
    puts stderr "FAIL: $f"
    return
}


# discover our current ip address 
set token [::http::geturl $CheckIp(url) -timeout $CheckIp(timeout)]
set status [::http::status $token]
set body [::http::data $token]
http::cleanup $token

set expression {([\d]+[\.][\d]+[\.][\d]+[\.][\d]+)}

if {[string match -nocase {ok} $status]} {
    # extract the ip address from the html response
    set count [regexp -nocase -expanded $expression $body all addr]
    if { $count < 1 } {
        puts stderr "$timestamp"
        puts stderr "could not find an IP address in the http response"
        puts stderr "$body"
    } elseif { $addr != $PrevState(addr) } {
        # write new state to log file.
        set f [open $path "a"]
        puts $f "$timestamp $addr"
        close $f
    }
} else {
    puts stderr "$timestamp"
    puts stderr "http status: $status"
}

