#! /usr/bin/tclsh 

puts stdout {<table border="1" cellpadding="10">}
while { ![eof stdin] } {
   set len [gets stdin csv]
   set row [split $csv ","]
   puts stdout "<tr>"
   foreach item $row { 
      puts stdout "\t<td> $item </td>"
   }
   puts stdout "</tr>"
}
puts stdout "</table>"
