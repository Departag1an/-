#include <cstdio>

#define Dtype long long 

using namespace std;
//FAST input
void in(Dtype * x) {
	* x = 0;
	char chace = getchar();
	int f = 1;
	while (chace - '0'<0 ||chace -'9'>0){
		if (chace == EOF || chace == '\n')
		{
			return;
		}
		if (chace == '-') {
			f = -1;
			chace = getchar();
			break;
		}
		chace = getchar();
	}
	if (chace - '0' < 0 || chace - '9' > 0)return;
	while (chace - '0' >= -0 && chace - '9' <= 0) {
		*x *= 10;
		*x += chace - '0';
		chace = getchar();
	}
	*x *= f;
	return;

}
// FAST output
void out(Dtype x) {
	if (x < 0) { putchar('-'),x =-x; }
	if (x < 10) { putchar(x + '0'); }
	else { out(x / 10); putchar(x % 10 + '0'); }
}
#define KMP_type char



// KMP
void get_next(KMP_type * pattern, int * next,int pattern_len) {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < pattern_len) {
		if (j == -1 || pattern[i] == pattern[j]) {
			i++, j++;
			next[i] = j;
		}
		else j = next[j];
	}
}

// KMP search
int KMP_search(KMP_type * text, KMP_type * pattern, int text_len, int pattern_len, int next[]) {
	int i = 0, j = 0, next[pattern_len];
	get_next(pattern, next, pattern_len);
	while (i < text_len && j < pattern_len) {
		if (j == -1 || text[i] == pattern[j]) {
			i++, j++;
		}
		else j = next[j];
	}
	if (j == pattern_len) return i - j;
	else return -1;
}
//BFS 
void BFS(int ** graph, int n, int start, int end, int * visited) {
	int queue[n], front = 0, rear = 0;
	queue[rear++] = start;
	visited[start] = 1;
	while (front < rear) {
		int u = queue[front++];
		if (u == end) {
			printf("Found\n");
			return;
		}
		for (int i = 0; i < n; i++) {
			if (graph[u][i] &&!visited[i]) {
				queue[rear++] = i;
				visited[i] = 1;
			}
		}
	}
	printf("Not Found\n");
}
//DFS 
void DFS(int ** graph, int n, int start, int end, int * visited) {
	visited[start] = 1;
	if (start == end) {
		printf("Found\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		if (graph[start][i] && !visited[i]) {
			DFS(graph, n, i, end, visited);
		}
	}
}	
//Dijkstra 
void Dijkstra(int ** graph, int n, int start, int end, int * dist,	int * visited)	 {
	for (int i = 0; i < n; i++) {
		dist[i] = graph[start][i];
	}
	dist[start] = 0;
	for (int i = 0; i < n - 1; i++) {
		int min_dist = 1e9, u = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && dist[j] < min_dist) {
				min_dist = dist[j];
				u = j;
			}
		}
		if (u == -1) break;
		visited[u] = 1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && graph[u][j]) {
				if (dist[u] + graph[u][j] < dist[j]) {
					dist[j] = dist[u] + graph[u][j];
				}
			}
		}
	}
}
//Floyd Warshall 
void FloydWarshall(int ** graph, int n, int ** dist) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != 1e9 && dist[k][j] != 1e9) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dist[i][j] == 1e9) {
				dist[i][j] = -1;
			}
		}
	}
}
//Bellman-Ford 
void BellmanFord(int ** graph, int n, int start, int * dist, int * visited) {
	for (int i = 0; i < n; i++) {
		dist[i] = graph[start][i];
	}
	dist[start] = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (dist[j] != 1e9 && graph[j][k] != 1e9) {
					if (dist[j] + graph[j][k] < dist[k]) {
						dist[k] = dist[j] + graph[j][k];
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dist[j] != 1e9 && graph[j][i] != 1e9) {
				if (dist[j] + graph[j][i] < dist[i]) {
					printf("Negative cycle\n");
					return;
				}
			}
		}
	}
}	
//LCA 
int LCA(int ** graph, int n, int u, int v) {
	if (u == v) return u;
	for (int i = 0; i < n; i++) {
		if (graph[u][i] && graph[v][i]) {
			return LCA(graph, n, i, v);
		}
	}
	return -1;
}

//sort
//merge sort
void merge(int * arr, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int * arr, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

//quick sort
int partition(int * arr, int l, int r) {
	int pivot = arr[r];
	int i = l - 1;
	for (int j = l; j < r; j++) {
		if (arr[j] <= pivot) {
			i++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = temp;
	return i + 1;
}

void quickSort(int * arr, int l, int r) {
	if (l < r) {
		int pi = partition(arr, l, r);
		quickSort(arr, l, pi - 1);
		quickSort(arr, pi + 1, r);
	}
}

//heap sort
void heapify(int * arr, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest]) {
		largest = l;
	}
	if (r < n && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, n, largest);
	}
}

void heapSort(int * arr, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0);
	}
}

//binary search
int binarySearch(int * arr, int l, int r, int x) {
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (arr[mid] == x) {
			return mid;
		}
		else if (arr[mid] < x) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return -1;
}





int main() {
	Dtype x;
	in(&x);
	out(x);


	return 0;
}



