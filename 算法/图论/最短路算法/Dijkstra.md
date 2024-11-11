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