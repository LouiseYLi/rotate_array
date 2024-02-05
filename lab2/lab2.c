#include <stdio.h>
#include <stdlib.h>

// update this with your A number
char a_num[] = "01377263";

void rotateArray(int arr[10][10], int n, int rows, int cols) {
    int size = rows;

    if (n % 90 != 0) {
        // Commented out due to restriction.
        // printf("Error. n must be a multiple of 90.\n");
        return;
    }
    
    // Number of rotations.
    int rotations = n / 90;
    // Subtracts full rotations from number of rotations.
    while (rotations > 3) {
        rotations -= 4;
    }
    while (rotations < -3) {
        rotations += 4;
    }

    // 0 is false, 1 is true.
    int hasExecuted = 0;
    int maxRotations = 1;
    for (int totalRotation = 0; totalRotation < maxRotations; totalRotation++) {
        // If statement for readability.
        if (!hasExecuted) {
            switch (rotations) {
                case 0:
                    maxRotations = 5;
                    break;
                case -1:
                case 1:
                    break;
                case -2:
                case 2:
                    maxRotations += 1;
                    break;
                case -3:
                case 3:
                    maxRotations += 2;
                    break;
            }
            hasExecuted = 1;
        }

        // Breaks out of loop because no rotations are required.
        if (maxRotations == 5) {
            break;
        }

        // Checks whether to rotate clockwise or counter clockwise.
        if (rotations < 0) {
            // Rotates counter clockwise.
            for (int i = 0; i < size / 2; i++) {
                for (int j = i; j < size - i - 1; j++) {
                    int temp = arr[i][j];
                    arr[i][j] = arr[j][size - 1 - i];
                    arr[j][size - 1 - i] = arr[size - 1 - i][size - 1 - j];
                    arr[size - 1 - i][size - 1 - j] = arr[size - 1 - j][i];
                    arr[size - 1 - j][i] = temp;
                }
            }
        } else if (rotations > 0) {
            // Rotates clockwise.
            for (int i = 0; i < size / 2; i++) {
                for (int j = i; j < size - i - 1; j++) {
                    int temp = arr[i][j];
                    arr[i][j] = arr[size - 1 - j][i];
                    arr[size - 1 - j][i] = arr[size - 1 - i][size - 1 - j];
                    arr[size - 1 - i][size - 1 - j] = arr[j][size - 1 - i];
                    arr[j][size - 1 - i] = temp;
                }
            }
        }
    }

    // Do NOT write any code below
    // Output the rotated array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int rotationAngle = 0;
    int dimensions = 0;
    int arr[10][10] = {0};  // Initialize the array with zeros
    int rows = 0, cols = 0;
    char inputChar;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the first line for angle of rotation and second line for array dimensions
    fscanf(file, "%d", &rotationAngle);
    fscanf(file, "%d", &dimensions);
    // Read the input array character by character
    int counter = 0; //To skip first two lines in the file
    while (rows < 10 && (inputChar = fgetc(file)) != 'E') {
        if (inputChar == '\n'){counter++;}
        if (inputChar == '\n' && counter>=2) {
            rows++;
            cols = 0;
        } else if (cols < 10 && inputChar >= '0' && inputChar <= '9') {
            arr[rows][cols++] = inputChar - '0';
        }
    }

    fclose(file);
    printf("A%s\n", a_num);
    // Actual dimensions of the input array
    rows = cols = dimensions;

    printf("Input array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nRotated array (%d degrees):\n", rotationAngle);
    rotateArray(arr, rotationAngle, rows, cols);

    return 0;
}
