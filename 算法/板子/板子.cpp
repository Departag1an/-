#include <cstdio>

#define Dtype int

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




int main() {
	Dtype x;
	in(&x);
	out(x);


	return 0;
}



