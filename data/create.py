import numpy as np

n = 1_000

x = np.random.rand(n)
y = np.random.rand(n)
f = open('rand.txt', 'a')
for a, b in zip(x, y):
  f.write(str(a) + "\n")
  f.write(str(b) + "\n")
f.close()

x = np.random.rand(n)
y = np.random.randn(n)
f = open('flat.txt', 'a')
for a, b in zip(x, y):
  f.write(str(a) + "\n")
  f.write(str(b) + "\n")
f.close()

x = np.random.rand(n) * 10
y = x + np.random.randn(n)
f = open('positive.txt', 'a')
for a, b in zip(x, y):
  f.write(str(a) + "\n")
  f.write(str(b) + "\n")
f.close()

theta = np.linspace(0, 2*np.pi, n)
phi = np.random.randn(n) + 10
x = phi * np.cos(theta)
y = phi * np.sin(theta)
f = open('donut.txt', 'a')
for a, b in zip(x, y):
  f.write(str(a) + "\n")
  f.write(str(b) + "\n")
f.close()

n = 1_000_000

x = np.random.rand(n)
y = np.random.rand(n)
f = open('bigrand.txt', 'a')
for a, b in zip(x, y):
  f.write(str(a) + "\n")
  f.write(str(b) + "\n")
f.close()
