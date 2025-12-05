

f = open("input.txt", "r")
file_content = f.readlines()
f.close()

def solve_puzzle_one(file_content):
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
  
  return total

def solve_puzzle_two(file_content):
  fresh_ids = set()
  all_ranges = []
  total = 0
  
  for line in file_content:
    if (len(line.strip()) == 0):
      break
    start, end = line.strip().split("-")
    
    start = int(start)
    end = int(end)
    all_ranges.append([start, end])
    
  all_ranges.sort()
  
  combined_ranges = []
  combined_ranges.append(all_ranges[0])
  
  for range in all_ranges:
    start = range[0]
    end = range[1]
    if start >= combined_ranges[-1][0] and start <= combined_ranges[-1][1]:
      combined_ranges[-1][1] = max(end, combined_ranges[-1][1])
    else:
      combined_ranges.append(range)
    
  for range in combined_ranges:
    total += range[1] - range[0] + 1
  
  return total

print(solve_puzzle_two(file_content))