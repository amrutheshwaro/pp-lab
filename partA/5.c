#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

void populatePoints(int points[][2], int n) {
    int i;
    for (i = 0; i < n; i++) {
        points[i][0] = rand() % 100;
        points[i][1] = rand() % 100;
    }
}

float calculateDistance(int x1, int y1, int x2, int y2) {
    int x = x1 - x2, y = y1 - y2;
    return ((float)sqrt(x*x + y*y));
}

void classifyPoints(int points[][2], int n) {
    int clusters[][2] = {{25, 25}, {25, 75}, {75, 75}, {75, 25}};
    int clusterCount[] = {0, 0, 0, 0};
    int i, j, clusterIndex;
    float min_distance, cur_distance;
    #pragma omp parallel for private(i, j, clusterIndex, min_distance, cur_distance)
        for (i = 0; i < n; i++) {
            min_distance = __FLT_MAX__;
            for (j = 0; j < 4; j++) {
                cur_distance = calculateDistance(points[i][0], points[i][1], clusters[j][0], clusters[j][1]);
                if (cur_distance < min_distance) {
                    min_distance = cur_distance;
                    clusterIndex = j;
                }
            }
            printf("The point (%d, %d) belongs to the cluster (%d, %d).\n", points[i][0], points[i][1], clusters[clusterIndex][0], clusters[clusterIndex][1]);
            clusterCount[clusterIndex]++;
        }
    printf("The number of points in each cluster is\n");
    for (i = 0; i < 4; i++)
        printf("(%d, %d) -> %d.\n", clusters[i][0], clusters[i][1], clusterCount[i]);
}

void main() {
    int n;
    printf("Enter the number of points to be generated.\n");
    scanf("%d", &n);
    int points[n][2];
    populatePoints(points, n);
    float start = omp_get_wtime();
    classifyPoints(points, n);
    float end = omp_get_wtime();
    printf("The time taken for execution is %f.\n", end - start);
}