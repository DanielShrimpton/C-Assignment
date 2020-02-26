import numpy as np
chars = {0: '.', 1: '*'}
write_to_file = []
for j in range(56):
    line = ''
    for i in range(512):
        line += chars[np.random.randint(0,high=2)]
    write_to_file.append(line)

with open("512.txt", "w") as f:
    for line in write_to_file:
        f.write(line)
        f.write('\n')
