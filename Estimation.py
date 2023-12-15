import pandas as pd
import numpy as np

dat = pd.read_csv("data.csv", index_col=None)
dp = dat[dat.PID==0]
da = dat[dat.PID==1]

tab = dp[(dp.pT==0.4)].sort_values('RelativeError', ascending=False)[:10]
print("Top 10: relative error (proton)")
print(tab)

tab = da[(da.pT==0.4)].sort_values('RelativeError', ascending=False)[:10]
print("Top 10: relative error (antiproton)")
print(tab)

# Here set parameters

# number of current embedding events
n = 1345107 

# current pt range
pt1 = [0.0, 5.0] 
# new pt range
pt2 = [0.2, 2.2]

gamma1 = (pt2[1] - pt2[0]) / (pt1[1] - pt1[0])

# current y range
y1 = [-1.55, 1.55]
# new y range
y2 = [-0.8, 0.8]

gamma2 = (y2[1] - y2[0]) / (y1[1] - y1[0])

# Vz: gamma = 1
gamma3 = 1.0

# target relative error (percent)
t = 2

# max relative error
mp = dp[dp.pT==0.4].RelativeError.max()
ma = da[da.pT==0.4].RelativeError.max()
deltap = (mp / t) ** 2 - 1
deltaa = (ma / t) ** 2 - 1

factor = gamma1 * gamma2 * gamma3 * n

n2p = deltap * factor
n2a = deltaa * factor

print(f'Proton')
print(f'max relative error = {mp}')
print(f'gamma (pt) = {gamma1}')
print(f'gamma (y) = {gamma2}')
print(f'gamma (Vz) = {gamma3}')
print(f'delta = {deltap}')
print(f'n = {n}')
print(f'n(add) = {n2p}')

print(f'AntiProton')
print(f'max relative error = {ma}')
print(f'gamma (pt) = {gamma1}')
print(f'gamma (y) = {gamma2}')
print(f'gamma (Vz) = {gamma3}')
print(f'delta = {deltaa}')
print(f'n = {n}')
print(f'n(add) = {n2a}')
