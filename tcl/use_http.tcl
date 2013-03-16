#!/usr/bin/tclsh
package require http

proc showState { fred } {
    upvar #0 $fred state

    foreach key [array names state] {
        puts "$key: $state($key)"
    }
}

proc showMetaData { wilma } {
    upvar #0 $wilma state
    foreach {key value} $state(meta) {
        puts "$key: $value"
    }
}

proc getCookies { varname } {
    upvar #0 $varname state
    set cookies [list]
    foreach {key value} $state(meta) {
        if { 0 == [string compare -nocase -length 10 $key "set-cookie"] } {
            lappend cookies $value
        }
    }
    return $cookies
       }


proc showCookies { varname } {
    foreach cookie [getCookies $varname] {
        puts "Cookie: $cookie"
    }
}

proc getRedirectUrl { varname } {
    upvar #0 $varname state
    set redirect_url ""
    set keyword "Location"
    foreach {key value} $state(meta) {
        if { 0 == [string compare -length [string length $keyword] $key "$keyword"] } {
            set redirect_url $value
            break
        }
    }
    return $redirect_url
       }


# ---------------------------------------------------------------------------

#set url "http://tycho.usno.navy.mil/cgi-bin/timer.pl"
#set url "http://www.largeformatphotography.info/forum/search.php"
#set url "http://www.apug.org/forums/"
       set url "http://www.apug.org/forums/search.php"
       set query [http::formatQuery do getdaily days 30]
#set url "http://www.r-project.org"

           set redirectCount 0
    while { $redirectCount < 3 && [info exists url] && [string length $url] } {
    set filename "body.html"
    set bodyfile [ open $filename "w"]

    if { [info exists query] && 0 < [string length $query] } {
        set token [http::geturl $url -channel $bodyfile -query $query]
    } else {
        set token [http::geturl $url -channel $bodyfile]
    }

    close $bodyfile

    puts ""
    puts "----------------------------------------------------------"
    puts "http State"
    puts "----------------------------------------------------------"
    showState $token

    puts ""
    puts "----------------------------------------------------------"
    puts "http meta-data"
    puts "----------------------------------------------------------"
    showMetaData $token

    puts ""
    puts "----------------------------------------------------------"
    puts "cookies"
    puts "----------------------------------------------------------"
    showCookies $token

    set url [getRedirectUrl $token]
    set query ""

    if { [string length $url] } {
        puts ""
        puts "----------------------------------------------------------"
        puts "redirects to: $url"
        puts "----------------------------------------------------------"
    }

    incr redirectCount

    http::cleanup $token

}

