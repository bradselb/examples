#! /usr/bin/tclsh
package require http

set filename [file native [file join . symbols.dat]]
set symbolfile [open "$filename" "r"]
set content [read $symbolfile]
close $symbolfile
set unsorted [split $content]
set symbols [lsearch -inline -all -sorted -not [lsort $unsorted] {}]
set s [join $symbols "+"]
set url "http://download.finance.yahoo.com/d/quotes.csv?s=$s&f=sd1t1hgl1c1v&e=.csv"
set token [::http::geturl $url]
set data [::http::data $token]
set errors [::http::error $token]
puts $data
if { [string length $errors] } { puts stderr "errors: $errors" }
::http::cleanup $token

exit


foreach s $symbols {
  set url "http://download.finance.yahoo.com/d/quotes.csv?s=$s&f=sd1t1hgl1c1v&e=.csv"
  set token [::http::geturl $url]
  set data [::http::data $token]
  set errors [::http::error $token]
  puts $data
  if { [string length $errors] } { puts stderr "errors: $errors" }
}
::http::cleanup $token

