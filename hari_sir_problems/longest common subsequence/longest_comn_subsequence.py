#finding the longest common sequence
x="AGGTAB"
y="GXTXAYB"
st = ""
def isvalid(st, y):
    l = []
    ar = []
    s = []
    for i in st:
        l.append(y.index(i))
    print l
    for i in range(len(l)-1):
        print i
        if l[i]<=l[i+1]:
            s.append(l[i])
            s.append(l[i+1])
        if l[i]>l[i+1]:
            ar.append(sorted(list(set(s))))
            s = []
    ar.append(sorted(list(set(s))))
    print ar
    for i in max(ar, key = len):
        print y[i]
    return st

for i in x:
    for j in y:
        if j == i:
            st+=j;
            break;
print isvalid(st, y)

