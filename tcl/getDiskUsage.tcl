#! /usr/bin/tclsh

set cmd "df -lT"
set fid [open "| $cmd" r]
set report [read $fid]
close $fid 

puts $report

foreach line [split $report "\n"] {
   set filesystem [lindex $line 0] 
   if { ![string equal -nocase -length 4  $filesystem {/dev}] } { continue }
   set device [lindex [split $filesystem {/}] 2]
   set fs_type [lindex $line 1]
   set fs_total_blocks [lindex $line 2]
   set fs_used_blocks [lindex $line 3]
   set fs_avail_blocks [lindex $line 4]
   set fs_mount_point [lindex $line 6]
   set fs_use_percent [expr { (100.0 * $fs_used_blocks) / ($fs_used_blocks + $fs_avail_blocks) } ]
   puts "device $device mounted on $fs_mount_point is $fs_use_percent percent used"
}

