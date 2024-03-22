import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('waveform.txt',sep=':',header=None)
data = pd.DataFrame(data)


x = data[0]
y = data[1]
plt.plot(x, y,'r--')
plt.show()