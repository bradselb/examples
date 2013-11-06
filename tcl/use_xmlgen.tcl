#! /usr/bin/tclsh

package require xmlgen 
namespace import ::xmlgen::*

declaretag head
declaretag html
declaretag body 
declaretag img
declaretag anchor a 

set imagefile [file join / home bselbrede garbage CaltarProSeries_210_6-1_a.jpg]

html ! { body ! { anchor href=$imagefile - click here} } 


