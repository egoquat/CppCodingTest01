#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int main__(void)
{
	int n = 0; float max = -1.0f;
	float* scores = nullptr;
	scanf("%d", &n);
	scores = new float[n];
	for (int i = 0; i < n; ++i) {
		scanf("%f", &scores[i]); max = std::max(max, scores[i]);
	}

	float sum = 0;;
	for (int i = 0; i < n; ++i) {
		sum += scores[i] / max * 100.0f;
	}

	float avg = (sum / n);
	printf("%02f", avg);
	delete[] scores;
	return 0;
}
