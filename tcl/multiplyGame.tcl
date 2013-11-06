#! /usr/bin/tclsh

set done 0
set wrong 0
set correct 0

puts "how many questions do you want? " 
gets stdin n 

puts "enter the leter q to quit"

   for {set i 1} { $i <= $n  && ! $done  } { incr i } {
      set x [expr { round( 12* rand() ) } ] 
      set y [expr { round( 9* rand() ) } ] 
      set answer [expr {$x * $y }]
      puts -nonewline "$i)  $x x $y = ? " ; flush stdout
      gets stdin z
      if { $z == "q" } { 
         set done 1 
	 break 
      } elseif { $z == $answer } { 
	 incr correct 
	 puts "  Correct!" 
      } else { 
         incr wrong 
	 puts "    WRONG! $x x $y = $answer" 
      } 
   }

puts "\nyou got $correct correct and $wrong wrong" 


