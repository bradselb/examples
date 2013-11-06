set tclver [info tcl]
puts "tcl version $tclver"

set reply {<h1 class="ip">Your <acronym title="Internet Protocol">IP</acronym> Address is: <span>67.108.13.66</span></h1>}
puts "$reply"

#set matchCount [regexp -nocase -expanded {(?:address) (?:[\s\w:\<]+[\>]) ([\d]+[\.][\d]+[\.][\d]+[\.][\d]+)}  $reply all addr]
set matchCount [regexp -nocase -expanded {([\d]+[\.][\d]+[\.][\d]+[\.][\d]+)}  $reply all addr]
puts "match count: $matchCount, all: '$all', address: '$addr'"

