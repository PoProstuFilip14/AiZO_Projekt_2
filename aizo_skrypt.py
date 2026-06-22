import subprocess
import time

#skrypt wykorzystywany do uruchamiania programu z różnymi parametrami podczas badań

EXE_PATH = r"C:\Users\froma\Documents\AiZO_Projekt_2\build\AiZOProjekt2.exe"

start_time = time.perf_counter()

p = "0"
a = "1"
s = "1"
l = "100"
d = "50"
n = "50"
it = 1

print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_100"])
it += 1
l = "200"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_200"])
it += 1
l = "400"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_400"])
it += 1
l = "600"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_600_50"])
it += 1
d = "25"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_600_25"])
it += 1
d = "75"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_600_75"])
it += 1
d = "99"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_600_99"])
it += 1
d = "50"
l = "800"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_800"])
it += 1
l = "1000"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_array_1000"])
it += 1
l = "100"
s = "2"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_100"])
it += 1
l = "200"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_200"])
it += 1
l = "400"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_400"])
it += 1
l = "600"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_600_50"])
it += 1
d = "25"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_600_25"])
it += 1
d = "75"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_600_75"])
it += 1
d = "99"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_600_99"])
it += 1
d = "50"
l = "800"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_800"])
it += 1
l = "1000"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "prim_list_1000"])
it += 1
l = "100"
p = "1"
a = "3"
s = "1"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_100"])
it += 1
l = "200"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_200"])
it += 1
l = "400"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_400"])
it += 1
l = "600"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_600_50"])
it += 1
d = "25"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_600_25"])
it += 1
d = "75"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_600_75"])
it += 1
d = "99"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_600_99"])
it += 1
d = "50"
l = "800"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_800"])
it += 1
l = "1000"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_array_1000"])
it += 1
l = "100"
s = "2"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_100"])
it += 1
l = "200"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_200"])
it += 1
l = "400"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_400"])
it += 1
l = "600"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_600_50"])
it += 1
d = "25"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_600_25"])
it += 1
d = "75"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_600_75"])
it += 1
d = "99"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_600_99"])
it += 1
d = "50"
l = "800"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_800"])
it += 1
l = "1000"
print(it)
subprocess.run([EXE_PATH, "-b", "-p", p, "-a", a, "-s", s, "-l", l, "-d", d, "-n", n, "-r", "dijkstra_list_1000"])
it += 1
l = "100"

end_time = time.perf_counter()

execution_time = end_time - start_time

print(f"Czas wykonania: {execution_time:.6f} sekund")