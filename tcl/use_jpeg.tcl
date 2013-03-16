#! /usr/bin/tclsh

package require jpeg

proc foo {} {
    foreach fname [lsort -dictionary [glob [file join ~ Downloads *]]] {
        if [::jpeg::isJPEG $fname] {
            puts ""
            puts "$fname"
            foreach {key value} [::jpeg::formatExif [::jpeg::getExif $fname]] {
                if {[string length $value] < 65} {
                    puts "$key: $value"
                } else {
                    puts "$key: -------------"
                }
            }
        }
    }
}

foo

