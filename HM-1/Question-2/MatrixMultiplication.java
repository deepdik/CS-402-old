import java.util.Random;

public class MatrixMultiplication {

    public static void main(String[] args) {
        int rowsA = 1500;
        int colsA = 1300;
        int colsB = 1000;

        int[][] matrixA = genRandomIntMatrix(rowsA, colsA);
        int[][] matrixB = genRandomIntMatrix(colsA, colsB);

        long startTime = System.nanoTime();
        int[][] resultInt = multIntMatrices(matrixA, matrixB);
        long endTime = System.nanoTime();

        double durationInt = (endTime - startTime)/1000000000.0;
        System.out.println("Integer Matrix Multiplication Time Is : " + durationInt + " seconds");

        double[][] matrixADouble = genRandomDoubleMatrix(rowsA, colsA);
        double[][] matrixBDouble = genRandomDoubleMatrix(colsA, colsB);

        startTime = System.nanoTime();
        double[][] resultDouble = multDoubleMatrices(matrixADouble, matrixBDouble);
        endTime = System.nanoTime();

        double durationDouble = (endTime - startTime)/1000000000.0;
        System.out.println("Double Matrix Multiplication Time Is: " + durationDouble + " seconds");
    }

    public static int[][] genRandomIntMatrix(int rows, int cols) {
        Random random = new Random();
        int[][] matrix = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = random.nextInt(1000); // Change range as needed
            }
        }
        return matrix;
    }

    public static double[][] genRandomDoubleMatrix(int rows, int cols) {
        Random random = new Random();
        double[][] matrix = new double[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = random.nextDouble() * 1000.0; // Change range as needed
            }
        }
        return matrix;
    }

    public static int[][] multIntMatrices(int[][] A, int[][] B) {
        int rowsA = A.length;
        int colsA = A[0].length;
        int colsB = B[0].length;
        int[][] result = new int[rowsA][colsB];

        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                for (int k = 0; k < colsA; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return result;
    }

    public static double[][] multDoubleMatrices(double[][] A, double[][] B) {
        int rowsA = A.length;
        int colsA = A[0].length;
        int colsB = B[0].length;
        double[][] result = new double[rowsA][colsB];

        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                for (int k = 0; k < colsA; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return result;
    }
}
