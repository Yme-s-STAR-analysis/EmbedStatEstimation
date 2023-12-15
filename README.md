# Estimation of embedding statistics

version: 1.0

author: yghuang

date: 14.12.2023

## Quick guide

这个包的作用是为了根据已经有的embedding，计算出效率值，根据其统计误差，粗略估计还需要多少额外的统计量

新的request和旧的可能存在不同的接受度需求，因此会有3个额外的gamma因子用来修正不同的接受度导致的区别

使用方法：

1. 从CalcTpcEff得到root文件，里面保存了各个窗口下的pT-y依赖的TEfficiency

2. make，指定好路径，运行run，得到csv文件

3. 修改对应的参数，并运行Estimation.py，会输出各种参数以及需要的额外统计量

## Patch note:

14.12.2023 by yghuang (v1.0):

> 第一个正式版本