## 朴素的dijkstra算法
```c++

const int N = 1000;		
const int INF = 0x3f3f3f3f;

int h[N], e[N], w[N], ne[N], idx;  
int dist[N];    	                   
bool visited[N];                  

void init() {
	std::fill(h, h + N, -1);
	idx = 0;
}

	
void addEdge(int a, int b, int weight) {
	e[idx] = b;
	w[idx] = weight;
	ne[idx] = h[a];
	h[a] = idx++;
}

 
void dijkstra(int start) {
	std::memset(dist, 0x3f, sizeof dist);   
	std::memset(visited, false, sizeof visited);  
	dist[start] = 0;			

	for (int i = 0; i < N; i++) {
		int u = -1, minDist = INF;
		for (int j = 0; j < N; j++) {
			if (!visited[j] && dist[j] < minDist) {
				u = j;
				minDist = dist[j];
			}
		}

		if (u == -1) break;

		visited[u] = true;
		for (int i = h[u]; i != -1; i = ne[i]) {
			int v = e[i], weight = w[i];
			if (dist[u] + weight < dist[v]) {   
				dist[v] = dist[u] + weight;
			}
		}
	}
}

```
## 堆优化的
```c++

const int N = 1000;		
const int INF = 0x3f3f3f3f;

int h[N], e[N], w[N], ne[N], idx;  
int dist[N];    	                   
bool visited[N];                  

void init() {
	std::fill(h, h + N, -1);
	idx = 0;
}

	
void addEdge(int a, int b, int weight) {
	e[idx] = b;
	w[idx] = weight;
	ne[idx] = h[a];
	h[a] = idx++;
}

 
void dijkstra(int start) {
	std::memset(dist, 0x3f, sizeof dist);   
	std::memset(visited, false, sizeof visited);  
	dist[start] = 0;

	 
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
	pq.push({ 0, start });  

	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();  

		if (visited[u]) continue;           
		visited[u] = true;
	
		 
		for (int i = h[u]; i != -1; i = ne[i]) {
			int v = e[i], weight = w[i];
			if (dist[u] + weight < dist[v]) {   
				dist[v] = dist[u] + weight;
				pq.push({ dist[v], v });         
			}
		}
	}
}

```
## 讨论
**你们有没有发现dijkstra算法和dfs与bfs实际上很相似，他们的区别是在`维护容器`与出入维护的不同上，dijkstra算法维护的是`优先队列`，而dfs与bfs维护的是`栈`或者`队列`。而且他在'入'时贪心地维护了dist,区别也就是如此**