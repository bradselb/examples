#! /usr/bin/tclsh

while {1} {
    set fil [open [file join / sys class thermal thermal_zone0 temp] {r}]
    set temp [expr {[read $fil] * 0.001}]
    close $fil
    puts $temp
    after 1000
}

