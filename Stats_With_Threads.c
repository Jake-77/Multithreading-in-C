#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

float avg;
int max;
int min;
float med;
int argCount;

void* average(void *param);
void* maximum(void *param);
void* minimum(void *param);
void* median(void *param);
int SortComp(const void *x, const void *y);

int main(int argc, char *argv[]) {

	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;

	argCount = argc;

	pthread_attr_t attr;

	if (argc < 2) {

		printf("You didn't pass any values in the terminal");
		return -1;
	}

	int *vals = (int*) malloc((argc - 1) * sizeof(int));

	for (int i = 1; i < argc; i++) {

		vals[i - 1] = atoi(argv[i]);
	}

	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, average, (void*) vals);
	pthread_create(&tid2, &attr, maximum, (void*) vals);
	pthread_create(&tid3, &attr, minimum, (void*) vals);
	pthread_create(&tid4, &attr, median, (void*) vals);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);

	printf("The average value calculated by the first thread is %.2f\n", avg);
	printf("The maximum value calculated by the second thread is %d\n", max);
	printf("The minimum value calculated by the third thread is %d\n", min);
	printf("The median value calculated by the fourth thread is %.2f\n", med);
	free(vals);

}

void* average(void *param) {

	int sum = 0;
	int *vals = (int*) param;

	for (int i = 0; i < argCount - 1; i++) {

		sum += vals[i];
	}
	avg = (float) sum / (argCount - 1);
	pthread_exit(0);

}

void* maximum(void *param) {

	int *vals = (int*) param;
	max = vals[0];

	for (int i = 1; i < argCount - 1; i++) {

		if (vals[i] > max) {

			max = vals[i];
		}
	}
	pthread_exit(0);
}

void* minimum(void *param) {

	int *vals = (int*) param;
	min = vals[0];

	for (int i = 1; i < argCount - 1; i++) {

		if (vals[i] < min) {

			min = vals[i];
		}
	}
	pthread_exit(0);
}

void* median(void *param) {

	int *vals = (int*) param;
	int i;
	int j;
	qsort(vals, argCount - 1, sizeof(int), SortComp);

	if ((argCount - 1) % 2 == 0) {

		i = argCount / 2;
		j = i - 1;
		med = (float) (vals[i] + vals[j]) / 2;

	} else {

		i = argCount / 2;
		med = (float) vals[i];
	}
	pthread_exit(0);
}

int SortComp(const void *x, const void *y) {

	int valX = *((int*) x);
	int valY = *((int*) y);

	if (valX == valY)
		return 0;

	else if (valX > valY)
		return 1;

	else
		return -1;
}

