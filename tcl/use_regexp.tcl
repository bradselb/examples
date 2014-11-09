#! /usr/bin/tclsh 

set tclver [info tcl]
puts "tcl version $tclver"

set reply {<h1 class="ip">Your <acronym title="Internet Protocol">IP</acronym> Address is: <span>67.108.13.66</span></h1>}
#puts "$reply"

set expression {([\d]+[\.][\d]+[\.][\d]+[\.][\d]+)}
set matchCount [regexp -nocase -expanded $expression $reply all addr]

puts "match count: $matchCount"
puts "all: '$all'"
puts "address: '$addr'"

