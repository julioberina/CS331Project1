$content = ""
$realtime = []
$seconds = 0

File.open(ARGV[0], "r").each do |line|
  $content += line
end

$content.scan(/real\s+\dm\d+\.\d+s/) do |real|
  real.scan(/\dm\d+\.\d+s/) { |time| $realtime << time }
end

$realtime.each do |time|
  time = time.split("m")
  time[1][-1] = ""
  $seconds += time[1].to_f
  $seconds += (time[0].to_f * 60) unless time[0].to_i.zero?
end

$seconds /= 10.0
puts "Average time:  #$seconds"
