
$1/calc_integral configs/de_jong.yaml logs/de_jong.csv
python3 plot_logs.py logs/de_jong.csv figs/de_jong.png

$1/calc_integral configs/shubert.yaml logs/shubert.csv
python3 plot_logs.py logs/shubert.csv figs/shubert.png

$1/calc_integral configs/ackley.yaml logs/ackley.csv
python3 plot_logs.py logs/ackley.csv figs/ackley.png

$1/calc_integral configs/langermann.yaml logs/langermann.csv
python3 plot_logs.py logs/langermann.csv figs/langermann.png

