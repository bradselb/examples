proc ic { focus theta } {
   set pi [expr { acos(-1) }]
   set theta_rad [expr {$theta * $pi / 180}]
   set diam [expr {2.0 * $focus * tan($theta_rad / 2.0)}]
   return $diam
}

proc aov { focus width } {
   set pi [expr {acos(-1)}]
   set theta_rad [expr {2.0 * atan((0.5 * $width) / $focus)}]
   set theta [expr {$theta_rad * 180.0 / $pi}]
   return $theta
}

proc invTv { n } {
   set k [expr { -1 * $n }]
   expr { pow(2.0, $k) }
}

proc invAv { n } { 
   set k [expr { $n / 2.0 }]
   expr { pow(2.0, $k) }
}

proc Tv { t } {
   expr { -1.0 * log(t) / log(2) }
}

proc Av { f } {
   expr { 2.0 * log($f) / log(2) }
}

