#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_students;
    int *grades;
    int i;

    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    if (num_students <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }
    
    grades = (int *)malloc(num_students * sizeof(int));

    if (grades == NULL) {
        printf("Error! Memory not allocated.\n");
        return 1;
    }

    printf("Enter the grades: ");
    for (i = 0; i < num_students; i++) {
        scanf("%d", &grades[i]);
    }

    int highest = grades[0];
    int lowest = grades[0];

    for (i = 1; i < num_students; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
        }

        if (grades[i] < lowest) {
            lowest = grades[i];
        }
    }

    printf("Highest grade: %d\n", highest);
    printf("Lowest grade: %d\n", lowest);

    free(grades);

    return 0;
}
