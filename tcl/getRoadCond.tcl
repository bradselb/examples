#!/usr/bin/tclsh

package require http
package require uri

proc doQuery {nr} {
	set scheme http 
	set host www.dot.ca.gov
	set path cgi-bin/roadscell.cgi
	set query [http::formatQuery roadnumber $nr]
	set url [uri::join scheme $scheme host $host path $path query $query]

	set token [http::geturl $url]
	set status [http::ncode $token]
	if {200 == $status} {
		puts "success"
		puts "[http::data $token]"
	}
	http::cleanup $token
}

foreach roadnumber $argv {
	puts "road number is: $roadnumber"
	doQuery $roadnumber
}
