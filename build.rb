#!/usr/bin/env ruby

require 'set'

abort "Usage: build.rb [target-file]" unless !ARGV[0].nil?

puts "Building application..."

src = File.read ARGV[0]

targets = Set.new
routes = Set.new
src.each_line do |entry|
  puts entry
  method = /(GET|POST)\s([\/\w|.*]*)\s([\/\w*]*.php)/.match(entry)[1]
  uri = /(POST|GET)\s([\/\w|.*]*)\s([\/\w*]*.php)/.match(entry)[2]
  file = /(POST|GET)\s([\/\w|.*]*)\s([\/\w*]*.php)/.match(entry)[3]
  cpp = "response_"+file.gsub(".php", ".hpp")
  name = file.gsub(/.php|-|_/, "")
  name = "Response"+name.capitalize
  targets.add [name, file, cpp]
  routes.add [method, uri, name]
end

include_str = ""
targets.each do |c|
  puts "Building #{c[1]}"
  Dir.chdir("build/seed") do
    abort "prepare.rb failed" unless system "../php2cpp/prepare.rb ./#{c[1]} ./_tmp.php"
    abort "php2cpp failed" unless system "../php2cpp/php2cpp ./_tmp.php ./_tmp.cpp #{c[0]}"
    abort "php2cpp failed" unless system "../php2cpp/uncrustify -c ../php2cpp/build/uncrustify/etc/gnu-indent.cfg -f _tmp.cpp > #{c[2]}"
  end
  include_str+="#include \"#{c[2]}\"\n"
end

routes_str=""
routes.each do |c|
  routes_str+="\t\t\tif(r.get_method()==\"#{c[0]}\" && r.get_path()==\"#{c[1]}\"){\n"
  routes_str+="\t\t\t\t#{c[2]} res(r);\n"
  routes_str+="\t\t\t\tres.compute();\n"
  routes_str+="\t\t\t\trtn=res;\n"
  routes_str+="\t\t\t\treturn rtn;\n"
  routes_str+="\t\t\t}\n"
end

src = File.read "./build/seed/response_factory.hpp"
src = src.gsub("/* routes:include */", include_str)
src = src.gsub("/* routes:switch */", routes_str)
outfile =  File.new("./build/seed/response_factory.hpp", "w+")
outfile.write src
