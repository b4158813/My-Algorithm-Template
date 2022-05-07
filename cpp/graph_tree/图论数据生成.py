from cyaron import *

n = 100000

m = 200000

s = randint(1,n)
t = randint(1,n)

graph = Graph.graph(n, m, weight_limit=5000) # 生成一个n点，m边的无向图，边权均为1
# graph = Graph.graph(n, m, directed=True, weight_limit=(5, 300)) # 生成一个n点，m边的有向图，边权范围是5到300

# graph = Graph.graph(n, m, weight_limit=20) # 生成一个n点，m边的无向图，边权范围是1到20
# graph = Graph.graph(n, m, weight_gen=my_func) # 生成一个n点，m边的无向图，使用自定义随机函数my_func的返回值作为边权
# graph = Graph.graph(n, m, self_loop=False, repeated_edges=False) # 生成一个n点，m边的无向图，禁止重边和自环
# # 以上的directed, weight_limit, weight_gen参数，对如下的所有函数都有效。

# chain = Graph.chain(n) # 生成一条n个节点的链，是Graph.tree(n, 1, 0)的别名
# flower = Graph.flower(n) # 生成一朵n个节点的菊花图，是Graph.tree(n, 0, 1)的别名
# tree = Graph.tree(n) # 生成一棵n个节点的随机树
# tree = Graph.tree(n, 0.4, 0.35) # 生成一棵n个节点的树，其中40%的节点呈现链状，35%的节点呈现菊花图状，剩余25%的节点随机加入
# binary_tree = Graph.binary_tree(n) # 生成一棵n个节点的随机二叉树
# binary_tree = Graph.binary_tree(n, 0.4, 0.35) # 生成一棵n个节点的二叉树，其中节点有40%的概率是左儿子，35%的概率是右儿子，25%的概率被随机选择
# graph = Graph.hack_spfa(n) # 生成一个n点，1.5*n(下取整)边的图，具有卡SPFA的特点
# graph = Graph.hack_spfa(n, extra_edge=m) # 生成一个n点，1.5*n+m(下取整)边的图，具有卡SPFA的特点
# # 下列方法生成的图保证连通
# # 支持 self_loop, repeated_edges, weight_limit, weight_gen 参数，但不支持 directed，DAG 的 self_loop 默认为 False
# graph = Graph.DAG(n, m) # 生成一个 n 点，m 边的有向无环图
# graph = Graph.DAG(n, m, loop=True) # 生成一个 n 点，m 边的有向有环图
# graph = Graph.UDAG(n, m) # 生成一个 n 点，m 边的无向联通图

io = IO('test1.in','test1.out')
io.input_writeln(n,m,s,t)
io.input_writeln(graph)
io.output_gen("./")