#define _CRT_SECURE_NO_WARNINGS
#define TASK_1
#include <stdio.h>
#include <stdlib.h>

#ifdef TASK_1
int main() {
  int array[14];
  int i;
  int sum = 0;
  int k = 0;
  for (i = 0; i < 14; i++) {
    scanf("%d", &array[i]);
  }
  for (i = 0; i < 14; i++) {
    if (array[i] % 2 == 0 && array[i] > 0) {
      k += 1;
      sum += array[i];
    }
  }
  printf("%d %d", k, sum);
  return 0;
}
#endif

#ifdef TASK_2
int main() {
  int array[17];
  int i;
  int sum = 0;
  for (i = 0; i < 17; i++) {
    scanf("%d", &array[i]);
  }
  for (i = 0; i < 17; i++) {
    if (array[i] % 2 != 0) {
      sum += array[i];
    }
  }
  for (i = 0; i < 17; i++) {
    if (array[i] % 3 == 0) {
      array[i] = sum;
    }
  }
  for (i = 0; i < 17; i++) {
    printf("%d ", array[i]);
  }
  return 0;
}
#endif

#ifdef TASK_3
int main() {
  float array[14];
  float q=0;
  int i=0;
  int j=0;
  for (i = 0; i < 14; i++) {
    scanf("%f", &array[i]);
  }
  for (i = 0; i < 14; i++) {
    for (j = 0; j < 7; j++) {
      if (array[j] > array[j + 1]) {
        q = array[j];
        array[j] = array[j + 1];
        array[j + 1] = q;
      }
    }
    for (j = 7; j < 14; j++) {
      if (array[j] < array[j + 1]) {
        q = array[j];
        array[j] = array[j + 1];
        array[j + 1] = q;
      }
    }
  }
  for (i = 0; i < 14; i++) {
    printf("%f ", array[i]);
  }
  return 0;
}
#endif

#ifdef TASK_4
int main() {
  float array[12];
  float max = 3.4028E-38;
  float min = 3.4028E+38;
  int imax;
  int imin;
  int i;
  int k;
  for (i = 0; i < 12; i++) {
    scanf("%f", &array[i]);
  }
  for (i = 0; i < 12; i++) {
    if (array[i] > max) {
      max = array[i];
      imax = i;
      }
    if (array[i] == max) {
      if (i > imax) {
        imax = i;
      }
    }
  }
  for (i = 0; i < 12; i++) {
    if (array[i] < min) {
      min = array[i];
      imin = i;
    }
    if (array[i] == min) {
      if (i < imin) {
        imin = i;
      }
    }
  }
  k = abs(imax - imin - 1);
  printf("%d", k);
  return 0;
}
#endif

#ifdef TASK_5
int main() {
  int array[15];
  int i;
  int k = 0;
  int p = 1;
  int n = 0;
  for (i = 0; i < 15; i++) {
    scanf("%d", &array[i]);
  }
  for (i = 0; i < 15; i++) {
    if (array[i] < 0) {
      k += 1;
    }
    if (array[i] == 0) {
      n += 1;
    }
  }
  for (i = 0; i < 15; i++) {
    if (array[i] > 0) {
      p = p * array[i];
    }
  }
  printf("%d %d %d", k, p, n);
  return 0;
}
#endif

#ifdef TASK_6
int main() {
  float array[12];
  int i = 0;
  float min = 3.4E38;
  float max = -3.4E-38;
  for (i = 0; i < 12; i++) {
    scanf("%f", &array[i]);
  }
  for (i = 0; i < 12; i++) {
    if (array[i] < min) {
      min = array[i];
    }
    if (array[i] > max) {
      max = array[i];
    }
  }
  printf("%f %f", min, max);
  return 0;
}
#endif

#ifdef TASK_7
int main() {
  int array[19];
  int i;
  int sum = 0;
  int k = 0;
  for (i = 0; i < 19; i++) {
    scanf("%d", &array[i]);
  }
  for (i = 0; i < 19; i++) {
    if (array[i] < 0) {
      k += 1;
    }
  }
  for (i = 0; i < 19; i++) {
    if (array[i] >= 0) {
      sum += array[i];
    }
    else {
      break;
    }
  }
  if (k == 0) {
    printf("-1");
  }
  else {
    printf("%d", sum);
  }
  return 0;
}
#endif

#ifdef TASK_8
int main() {
  int array[4][4];
  int transp[4][4];
  int i;
  int j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      scanf("%d", &array[i][j]);
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      transp[j][i] = array[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%d ", transp[i][j]);
    }
    printf("\n");
  }
  return 0;
}
#endif

#ifdef TASK_9
int main() {
  int array[4][4];
  int i;
  int j;
  int a;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      scanf("%d", &array[i][j]);
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (i == j) {
        a = array[i][j];
        array[i][j] = array[i][3 - j];
        array[i][3 - j] = a;
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
  return 0;
}
#endif

#ifdef TASK_10
int main() {
  int array[5][5];
  int i;
  int j;
  int sum = 0;
  int max = -32767;
  int min = 32767;
  int imax[2] = { 0, 0 };
  int imin[2] = { 0, 0 };
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      scanf("%d", &array[i][j]);
    }
  }
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (array[i][j]>max) {
        max = array[i][j];
        imax[0] = i;
        imax[1] = j;
      }
        if (array[i] == max) {
        if (i > imax[0]  j > imax[1]) {
          imax[0] = i;
          imax[1] = j;
        }
      }
    }
  }
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (array[i][j] < min) {
        min = array[i][j];
        imin[0] = i;
        imin[1] = j;
      }
      if (array[i] == min) {
        if (i < imin[0] || j < imin[1]) {
          imin[0] = i;
          imin[1] = j;
        }
      }
    }
  }
  for (int i = min(imax[0], imin[0]); i <= max(imax[0], imin[0]); i++) {
    for (int j = min(imax[1], imin[1]); j <= max(imax[1], imin[1]); j++) {
      sum += array[i][j];
    }
  }
  printf("%d", sum);
  return 0;
}
#endif