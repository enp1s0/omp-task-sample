#include <iostream>
#include <chrono>
#include <omp.h>

int f(const int v) {
	int v1, v2;
	if (v <= 2) {
		return 1;
	} else {
#pragma omp task shared(v1) firstprivate(v)
		v1 = f(v - 1);
#pragma omp task shared(v2) firstprivate(v)
		v2 = f(v - 2);
		#pragma omp taskwait
		return v1 + v2;
	}
}

int main(int argc, char** argv) {
	int n = std::stoi(argv[1]);
	int v;

	const auto start_clock = std::chrono::system_clock::now();
#pragma omp parallel shared(n)
	{
#pragma omp single
		v = f(n);
	}
	std::printf("%d\n", v);
	const auto end_clock = std::chrono::system_clock::now();
	std::printf("time=%.3f[s]\n", std::chrono::duration_cast<std::chrono::microseconds>(end_clock - start_clock).count() * 1e-6);
}
