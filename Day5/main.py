

f = open("input.txt", "r")
file_content = f.readlines()
f.close()

  
line_number = 0
fresh_id_ranges = []

for i, line in enumerate(file_content):
  if (len(line.strip()) == 0):
    line_number = i + 1
    break
  
  start, end = line.strip().split("-")
  start = int(start)
  end = int(end)
  
  fresh_id_ranges.append([start, end])
  
total = 0
for id in file_content[line_number:]:
  for range in fresh_id_ranges:
    if int(id) > range[0] and int(id) <= range[1]:
      total += 1
      break

print (total)