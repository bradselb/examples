#! /usr/bin/lua

-- a simple script to fetch a web page

local socket = require("socket")
local http = require("socket.http")
--[[
content = http.request("http://www.kernel.org/pub/linux/kernel/v3.0/ChangeLog-3.0.74")
--]]
content = http.request("http://www.dot.ca.gov/cgi-bin/roadscell.cgi?roadnumber=108")
print(content)
