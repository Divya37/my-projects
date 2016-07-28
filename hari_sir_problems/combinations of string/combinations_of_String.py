def combi(input):
    lis=['']
    for i in range(len(input)):
        s=[]
        for j in lis:
            s.append(j+input[i])
        lis+=s
    return lis[1:]

print combi('abcde')
