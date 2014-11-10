#! /usr/bin/tclsh

package require http

#set CheckIp(url) {http://checkip.dyndns.org}
#set CheckIp(timeout) 1000 ; # milliseconds
#set CheckIp(myIp) {127.0.0.1}
#set CheckIp(done) 0

array set CheckIp {
    url {http://checkip.dyndns.org:8245}
    timeout 5000
    myIp 127.0.0.1
}

set token [::http::geturl $CheckIp(url) -timeout $CheckIp(timeout)]
#upvar #0 $token state

set status [::http::status $token]
# puts  "$status"

set body [::http::data $token]
# puts stderr "$body"

http::cleanup $token

if {[string match -nocase {ok} $status]} {
    set expression {([\d]+[\.][\d]+[\.][\d]+[\.][\d]+)}
    set count [regexp -nocase -expanded $expression $body all addr]
    # puts stderr "match count: $count"
    # puts stderr "address match: '$addr'"
    if {[expr {$count > 0}]} {
        set CheckIp(myIp) $addr
    } else {
        puts stderr "could not find an IP address in the http response"
        puts stderr "$body"
    }
} else {
    puts stdout "http status: $status"
}

puts stdout "$CheckIp(myIp)"
