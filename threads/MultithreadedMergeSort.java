package threads;
import java.util.Arrays;

public class MultithreadedMergeSort {

    private static final int[] unsortedArray = {12, 34, 1, 16, 28, 13, 42, 8, 7, 64};
    private static int[] sortedArray;

    public static void main(String[] args) throws InterruptedException {
        int midIndex = unsortedArray.length / 2;
        sortedArray = new int[unsortedArray.length];

        // Create and start sorting threads
        Thread sortThread1 = new Thread(new Sorter(0, midIndex));
        Thread sortThread2 = new Thread(new Sorter(midIndex, unsortedArray.length));
        sortThread1.start();
        sortThread2.start();

        // Wait for sorting threads to complete
        sortThread1.join();
        sortThread2.join();

        // Create and start merging thread
        Thread mergeThread = new Thread(new Merger(0, midIndex, unsortedArray.length));
        mergeThread.start();
        mergeThread.join();

        // Output the sorted array
        System.out.println("Sorted Array: " + Arrays.toString(sortedArray));
    }

    static class Sorter implements Runnable {
        private final int start;
        private final int end;

        Sorter(int start, int end) {
            this.start = start;
            this.end = end;
        }

        @Override
        public void run() {
            Arrays.sort(unsortedArray, start, end);
        }
    }

    static class Merger implements Runnable {
        private final int start;
        private final int mid;
        private final int end;

        Merger(int start, int mid, int end) {
            this.start = start;
            this.mid = mid;
            this.end = end;
        }

        @Override
        public void run() {
            merge();
        }

        private void merge() {
            int leftIndex = start;
            int rightIndex = mid;
            int mergedIndex = start;

            while (leftIndex < mid && rightIndex < end) {
                if (unsortedArray[leftIndex] <= unsortedArray[rightIndex]) {
                    sortedArray[mergedIndex++] = unsortedArray[leftIndex++];
                } else {
                    sortedArray[mergedIndex++] = unsortedArray[rightIndex++];
                }
            }

            while (leftIndex < mid) {
                sortedArray[mergedIndex++] = unsortedArray[leftIndex++];
            }

            while (rightIndex < end) {
                sortedArray[mergedIndex++] = unsortedArray[rightIndex++];
            }
        }
    }
}

