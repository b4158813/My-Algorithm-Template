import pandas as pd
import numpy as np

data = np.random.randint(0,101,(10,10),np.int32)

index = np.arange(1,11,1)
matrix = pd.DataFrame(data, index,index)

print(matrix)

matrix_max = matrix.max(axis=1)
print(matrix_max)