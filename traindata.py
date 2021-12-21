# -*- coding: utf-8 -*-
"""
Created on Tue Dec 21 21:17:18 2021

@author: miken
"""

import numpy as np
from matplotlib import pyplot as plt
import pandas as pd
#from IPython import get_ipython

#get_ipython().run_line_magic('matplotlib', 'inline')
#%matplotlib inline

pd_data = pd.read_csv("./log_data.csv")
print(pd_data.head(5))

time_stamps = pd_data['time'].to_numpy()
velocities = pd_data['velocity'].to_numpy()
positions = pd_data['position'].to_numpy()


plt.plot(time_stamps, positions)
plt.xlabel('Abtastswerte [s]')
plt.ylabel('Position [m]')
plt.title('Zugposition')
plt.show()
