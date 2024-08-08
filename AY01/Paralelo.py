import numpy as np
from math import sqrt
from joblib import Parallel
from joblib import delayed
import time as tm

print("Comenzando a calcular...")
start = tm.time()
parallel_pool = Parallel(n_jobs=4)
parallel_sqrt = delayed(sqrt)
parallel_tasks = [parallel_sqrt(i) for i in range(10000000)]
parallel_results = parallel_pool(parallel_tasks)
end = tm.time()
print(f"Tiempo total: {end - start}s")