#!/usr/bin/ruby
# coding: utf-8

require 'pp'

$indent = 2

class Array;
  def nest; self[0] end
  def nest=(val); self[0]=val end
  def value; self[1] end
  def value=(val); self[1]=val end
  def comment; self[2] end
  def comment=(val); self[2]=val end
end

def nestlv(s)
  /^( *)/.match(s).captures.first.size / $indent
end

def exsplit(s)
  s.scan(/("[^"]*")|('[^']*')|([^ ]+)/).flatten.select{|m|m}
end

s = STDIN.read.gsub(/\\\n/, '').split(/\r?\n/).map(&:chomp)
s.map!{|c| [nestlv(c), c.gsub(/ *;.*$/, "").strip, c.gsub(/^.*?( *;.*)?$/, '\1')] }
s.push [0, "()"]

s.each_cons(2) do |c, n|
  if /^\s*$/ =~ c.value
    printf "%s%s\n", c.value, c.comment
    next
  end
  cont = c.nest < n.nest # continue to next line
  if !/^'?(?<p>\((?:[^()]|\g<p>)*\))$/.match(c.value)
    if exsplit(c.value).size > 1 && !cont
      c.value = "(%s)" % c.value
    end
  end
  printf " " * $indent * c.nest
  if cont
    printf("(" * (n.nest - c.nest))
  end
  printf "%s%s", c.value, c.comment
  if c.nest > n.nest
    printf(")" * (c.nest - n.nest))
  end
  printf "\n"
end

