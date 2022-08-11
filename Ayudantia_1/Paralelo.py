import numpy as np
from joblib import Parallel
from joblib import delayed

parallel_pool = Parallel(n_jobs=2)
parallel_sqrt = delayed(np.sqrt)
parallel_tasks = [parallel_sqrt(i) for i in range(10000000)]
parallel_results = parallel_pool(parallel_tasks)