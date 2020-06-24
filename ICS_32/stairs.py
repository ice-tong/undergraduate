#
# Kian Farsany
# Project 0
#

num = int(input())

for i in range(num):
    print('+-+')
    print(i*2 * ' ' + '| |')
    print(i*2 * ' ' + '+-', end = '')

if num > 0:
    print('+')
