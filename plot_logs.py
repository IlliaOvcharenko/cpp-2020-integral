import sys
import pandas as pd
import matplotlib.pyplot as plt

from pathlib import Path

log_filename = sys.argv[1]
fig_filename = sys.argv[2]
df = pd.read_csv(log_filename)

plt.figure(figsize=(15, 5))
plt.plot(df.groupby("n_threads").mean(), "-*", c="r")
plt.xlabel("num of threads")
plt.ylabel("time, s")
plt.title(Path(log_filename).stem)
plt.grid(alpha=0.5)
plt.savefig(fig_filename, bbox_inches="tight")
