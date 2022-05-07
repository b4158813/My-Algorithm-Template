n, m = map(int, input().split())
e = {i:[] for i in range(n+1)}
for _ in range(m):
    x, y, z = map(int, input().split())
    e[x].append([y, z])

def djkstra():  
    dis = [-1] * (n + 1)
    from queue import PriorityQueue 
    q = PriorityQueue()
    q.put((0, 1))
    while q.qsize() > 0:
        d, v = q.get()
        if dis[v] > 0:
            continue
        dis[v] = d 
        for item in e[v]:
            q.put((item[1] + d, item[0]))
    return dis

print(djkstra()[n])
