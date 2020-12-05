package hw4.hashing.sorting;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.time.MovingAverage;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.chart.ui.ApplicationFrame;
import javax.swing.*;
import java.awt.*;

class SortingComparison extends ApplicationFrame {

    private int comparisons;

    public SortingComparison(final String title) {

        super(title);

        // Collections that hold the series we are about to create
        final XYSeriesCollection divAndConqData = new XYSeriesCollection();
        final XYSeriesCollection quadraticData = new XYSeriesCollection();

        int maxSize = 5000;
        int dataRange = 1000;

        final XYSeries series1 = new XYSeries("quick sort k=0");
        // quick sort with no insertion sort
        // loop from 0 to maxSize
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) { //Add random values until that array size is full.
                data[j] = (int) (Math.random() * dataRange);
            }
            quickSort(data, 0, data.length - 1);
            series1.add(data.length, comparisons);
        }
        // create an array of each size and fill it with random elements using
        // (int) (Math.random() * dataRange)
        // sort using the method for this series
        // add data point to series like series1.add(size, comparisons);
        // ...
        // ...
        // ...
        // after adding all the data points, (there should be maxSize of them) add the
        // series to the collection for this graph
        divAndConqData.addSeries(series1);

        final XYSeries series2 = new XYSeries("quick sort k=10");
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            hybridQuickSort(data, 10, 0, data.length - 1);
            series2.add(data.length, comparisons);
        }
        // repeat above for quick sort with insertion sort for 10 or less elements
        divAndConqData.addSeries(series2);

        final XYSeries series3 = new XYSeries("quick sort k=20");
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            hybridQuickSort(data, 20, 0, data.length - 1);
            series3.add(data.length, comparisons);
        }
        // repeat above...
        divAndConqData.addSeries(series3);

        final XYSeries series4 = new XYSeries("quick sort k=50");
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            hybridQuickSort(data, 50, 0, data.length - 1);
            series4.add(data.length, comparisons);
        }
        // repeat above...
        divAndConqData.addSeries(series4);

        final XYSeries series5 = new XYSeries("merge sort");
        // reminder: merge sort with out-of-place merge so that we get O(n log n)
        // runtime
        // repeat above
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            mergeSort(data, 0, data.length - 1);
            series5.add(data.length, comparisons);
        }
        divAndConqData.addSeries(series5);

        // max size for quadratic sorts. we needs these to be smaller so that it doesn't
        // take too long
        maxSize = 500;
        final XYSeries series6 = new XYSeries("insertion sort");
        // repeat above...
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            insertionSort(data);
            series6.add(data.length, comparisons);
        }

        // adding to a different graph for quadtratic sort, but the process is the same
        quadraticData.addSeries(series6);

        final XYSeries series7 = new XYSeries("selection sort");
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            selectionSort(data);
            series7.add(data.length, comparisons);
        }
        // repeat above...
        quadraticData.addSeries(series7);

        final XYSeries series8 = new XYSeries("bubble sort");
        for (int i = 1; i <= maxSize; i++) {
            int[] data = new int[i];
            for (int j = 0; j < data.length; j++) {
                data[j] = (int) (Math.random() * dataRange);
            }
            bubbleSort(data);
            series8.add(data.length, comparisons);
        }
        // repeat above...
        quadraticData.addSeries(series8);

        // YOU DON'T REALLY NEED TO TOUCH THIS SECTION, BUT FEEL FREE TO LOOK THROUGH IT
        // =============================================================================================================
        // takes the data sets and turns them into a moving average so things are easier
        // to see
        XYDataset ma1 = MovingAverage.createMovingAverage(divAndConqData, "", 50, 0);
        XYDataset ma2 = MovingAverage.createMovingAverage(quadraticData, "", 50, 0);
        // takes the moving averages and plots them as line charts
        // if you want to see what it looks like without the moving average you can put
        // data1 and data2 directly in here instead of ma1 and ma2
        final JFreeChart chart1 = ChartFactory.createXYLineChart("Divide and conquer sorts", "Input size n",
                "Num comparisons", ma1, PlotOrientation.VERTICAL, true, true, false);
        final JFreeChart chart2 = ChartFactory.createXYLineChart("Quadratic sorts", "Input size n", "Num comparisons",
                ma2, PlotOrientation.VERTICAL, true, true, false);
        // panel/window setup
        // don't worry about this unless you want to mess with dimensions
        final ChartPanel chartPanel1 = new ChartPanel(chart1);
        final ChartPanel chartPanel2 = new ChartPanel(chart2);
        chartPanel1.setPreferredSize(new java.awt.Dimension(400, 270));
        chartPanel2.setPreferredSize(new java.awt.Dimension(400, 270));
        JPanel j = new JPanel();
        j.setLayout(new GridLayout());
        j.add(chartPanel1);
        j.add(chartPanel2);
        setContentPane(j);
        // =============================================================================================================
    }

    /*This method takes in an int array, and two integers that represents
     *the position of the element inside the array. It switches the position 
     *of the two elements in the array. This method is called by selection sort, 
     *bubble sort, and partition which is called by quick sort.
    
     *Parameter: int array, two ints for the two position of the elements 
     *that will be switched.
     */
    public void swap(int[] data, int a, int b) {
        int temp = data[a];
        data[a] = data[b];
        data[b] = temp;
    }

    /*This method takes in an int array, the first position of the array,
     *the middle and last position of the array. This method is out of place
     *because it contains two temporary arrays for sorting. It compares values
     *of the two temporary arrays and add them back into the int array parameter
     *in increasing order. This comparison takes O(n) times. It is called by the 
     *the merge sort method.
    
     *Parameters: data - the int array provided by the user which will be modified and sorted
                  first - first position of the sub array that was split
                  mid - the middle value which could is either the end of the left array or 
                        the beginning of the right array
                  last - the last positiono the sub array that was split
     *Return: data - the int array with partially sorted array.
     */
    public int[] merge(int[] data, int first, int mid, int last) {
        int[] tempLeft = new int[mid - first + 1]; // Temp array that takes elements from the first to middle position.
        int[] tempRight = new int[last - mid]; //Temp array that takes element from the middle to last position.

        for (int i = 0; i < tempLeft.length; i++) {
            tempLeft[i] = data[first + i];
        }
        for (int i = 0; i < tempRight.length; i++) {
            tempRight[i] = data[mid + 1 + i];
        }
        int leftPos = 0; //Counter for the first temp array.
        int rightPos = 0; //Counter for the second temp array. 
        int counter = first; //Counter to keep track of the current index of the original array. 
        for (; leftPos < tempLeft.length && rightPos < tempRight.length;) { //Loop stops when one of the temp arrays reaches the end. 
            comparisons++;
            if (tempLeft[leftPos] < tempRight[rightPos]) { //Checks if left array has a smaller value than the right array.
                data[counter] = tempLeft[leftPos];//If yes, then add that value to the original array.
                leftPos++;
            } else {
                data[counter] = tempRight[rightPos]; // Otherwise, add the right value to the original array.
                rightPos++;
            }
            counter++;
        }
        for (int i = counter; leftPos < tempLeft.length; i++) { // If the counter of the left array has not reach the end,
            data[i] = tempLeft[leftPos];// add the rest of the left array into the original array. 
            leftPos++;
        }
        for (int i = counter; rightPos < tempRight.length; i++) { //If the counter of the right array has not reach the end, 
            data[i] = tempRight[rightPos];// add the rest of the right array into the original array. 
            rightPos++;
        }

        return data;
    }

    /*This method is called by quick sort and it takes in an int array,
     *the first (which is also the pivot index) and last position of the array. It organizes the array through comparison
     *so that elements smaller than the pivot is to the left of the pivot and elements larger than the pivot is to the
     *right. This takes O(n) times.    
     *Parameters: data - the int array given by the user
     first - the first position of the array that will be partitioned
     last - the last position of the array that will be partitioned
     *Return: pivot index, which splits the array into values before the pivot and values after the pivot.
     */
    public int partition(int[] data, int first, int last) {
        int pivotIndex = first;
        int large = first + 1; //The index whose value will always be larger than the pivot value.
        for (int i = large; i <= last; i++) { //Going from the value after the pivot value to the last value
            comparisons++;
            if (data[i] <= data[pivotIndex]) { //If the particular value is less than the pivot, switch that value with  
                swap(data, i, large); // the value that is larger than pivot. 
                large++;
            }

        }
        swap(data, pivotIndex, large - 1); // Switch the pivot index with the value right before large, which is the last value that is smaller than pivot.
        return large - 1;
    }

    /*This method takes in int array and sorts the values in increasing order.
     *This is done in O(n^2) time.
    
     *Parameter: data - the int array that will be sorted.
     */
    public void selectionSort(int[] data) {
        comparisons = 0;
        int minLoc = 0; //This variable is use to store the location of the minimum value.
        for (int i = 0; i < data.length - 1; i++) {
            minLoc = i; // The position of the posible min location increments by one as the array gets more sorted.
            for (int j = i + 1; j < data.length; j++) {
                comparisons++;
                if (data[j] < data[minLoc]) { // Compare location of the minimum to the next value
                    minLoc = j; // If minimum location has the bigger value, then minLoc becomes the next index by swapping.
                    swap(data, minLoc, i);
                }
            }

        }
    }

    /*This method takes in int array and sorts the values in increasing order.
     *This is done in O(n^2) time. It finds the smallest element and inserts it
     *into the sorted part of the array. Thus, it is efficient (less than O(n^2) time)
     *on arrays that are almost sorted.
    
     *Parameter: data - the int array that will be sorted.
     */
    public void insertionSort(int[] data) {
        comparisons = 0;
        int j = 0;
        int temp = 0;
        for (int i = 1; i < data.length; i++) {
            j = i;
            temp = data[i]; //The value that will be compared with all other value.
            while (j > 0 && temp < data[j - 1]) {// If there are still values to be compared in the sorted part of the array 
                comparisons++; // and the value is less than the value before that, keep shifting that element leftwards.
                data[j] = data[j - 1];
                j--;
            }
            if (j <= 0) {// When j hits zero, there is still one comparison made.
                comparisons++;
            } else if (temp >= data[j - 1]) { // Otherwise, if the while loop was false, there is still one comparison made before breaking the loop.
                comparisons++;
            }
            data[j] = temp;

        }
    }
    /* This method takes an int array, an int for the first position of the array
     * and an int for the last position that this method will work on. This method 
     * is called by hybridQuickSort when the array reaches a certain size and sorts
     * the rest of the array. This improves the efficiency of comparisons. 
    
     * parameters: data - partially sorted int array that is passed from hybridQuickSort 
     *             first - the first index of the partial array
     last - the last index of the partial array
     */

    public void editInsertionSort(int[] data, int first, int last) {
        int j = 0;
        int temp = 0;
        int counter = 0; // Keeps count of the loop based on the size of the partial array 
        for (int i = first + 1; counter < last - first; i++) {
            j = i;
            temp = data[i]; // The value to be inserted into the sorted part of the array
            while (j > 0 && temp < data[j - 1]) { // If there are still values to be compared in the sorted part of the array and 
                comparisons++;
                data[j] = data[j - 1]; // and the value is less than the value before that, keep shifting that element leftwards.
                j--;
            }
            if (j <= 0) { // When j hits zero, there is still one comparison made.
                comparisons++;
            } else if (temp >= data[j - 1]) { // Otherwise, if the while loop was false, there is still one comparison made before breaking the loop.
                comparisons++;
            }
            data[j] = temp;
            counter++;
        }
    }

    /*This method takes in int array and sorts the values in increasing order.
     *This is done in O(n^2) time.
    
     *Parameter: data - the int array that will be sorted.
     */
    public void bubbleSort(int[] data) {
        comparisons = 0;
        for (int i = 0; i < data.length - 1; i++) {
            for (int j = data.length - 1; j > i; j--) {
                comparisons++;
                if (data[j] < data[j - 1]) {
                    swap(data, j, j - 1);
                }
            }
        }
    }

    /*This method takes in an int array, an int for the first position of 
     *of the array and an int for the last position of the array. This method 
     *recurively splits the array into halves (in place) until there is there 
     *is only one element. It then calls the merge method for a total of O(n log n)
     *runtime. 
    
     * parameters: data - partially sorted int array that is passed from hybridQuickSort 
     *             first - the first index of the partial array
     *             last - the last index of the partial array
     */
    public void mergeSort(int[] data, int first, int last) {
        if (last + 1 - first == data.length) { //If the array has not been split, first set comparisons to 0.
            comparisons = 0;
        }
        if (last - first > 0) { // If there is more than one element
            int mid = first + (last - first) / 2; // find the middle
            mergeSort(data, first, mid); // recursively split the first half of the array
            mergeSort(data, mid + 1, last); // recursively split the last half of the of the array
            merge(data, first, mid, last); // merge the two splitted arrays
        }
    }

    /*This method takes in an int array, an int for the first position of 
     *of the array and an int for the last position of the array. It splits
     *the array by the pivot index where values smaller than the pivot will 
     *go to the left and values larger than the pivot will go the right.The 
     *method recursively finds the next pivot index until there is one element.
     *Runtime of O(n log n).
    
     * parameters: data - an int array that becomes more sorted as more partitions happen
     *             first - the first index of the partial array
     *             last - the last index of the partial array
    */
    public void quickSort(int[] data, int first, int last) {
        if (last + 1 - first == data.length) { //If the array has not be split, first set comparisons to 0.
            comparisons = 0;
        }
        if (last - first > 0) { // If there is more than one element
            int pivotIndex = partition(data, first, last); //call the partition method and return the pivot index
            quickSort(data, first, pivotIndex - 1); //split the first part of the array  
            quickSort(data, pivotIndex + 1, last); //split the second part of the array
        }

    }
    
    /*This method takes in an int array, an int k that tells the program to change 
     *to insertion sort once it reaches the kth element, an int first that represents 
     *the first position of the partial array and an int last that represents the last position
     *of the partial array. It recursively calls the parition method to obtain the pivot index
     *and split the array. Then, the method calls editInsertIonSort once the partial array reaches the 
     *k th size. The right k value would decrease the number of comparisons. 
     *Runtime of O(n log n).
    
     * parameters: data - an int array that becomes more sorted as more partitions happen
     *             first - the first index of the partial array
     *             k - the size of the array where edit insertion sort will be used 
     *             last - the last index of the partial array
    */
    public void hybridQuickSort(int[] data, int k, int first, int last) {
        if (last + 1 - first == data.length) {//If the array has not been split, first set comparisons to 0. 
            comparisons = 0;
        }
        if (last - first > k) { // if the partial array's size is greater than k, continue with quick sort
            int pivotIndex = partition(data, first, last);
            hybridQuickSort(data, k, first, pivotIndex - 1);
            hybridQuickSort(data, k, pivotIndex + 1, last);
        } else { //otherwise, use the editted insertion sort
            editInsertionSort(data, first, last);
        }

    }

    public static void main(String[] args) {
        // EXAMPLE TESTS

        // int[] arr1 = { 1, 2, 3, 4, 5, 6, 7 };
        // sort(arr1, 0, arr1.length - 1, 5);
        // for (int x: arr1)
        // System.out.println(x);
        // System.out.println();
        // int[] arr2 = { 7, 6, 5, 4, 3, 2, 1};
        // hybridQuickSort(arr2, 0, arr2.length - 1, 5);
        // for (int x: arr2)
        // System.out.println(x);
        // System.out.println();
        // int[] arr3 = { 56, 3, 78, 26, 1276, 123, 45, 34};
        // hybridQuickSort(arr3, 0, arr3.length - 1, 5);
        // for (int x: arr3)
        // System.out.println(x);
        // System.out.println();
        // call constructor for our ApplicationFrame which will set up all the test
        // sorts and plot the results
        final SortingComparison window = new SortingComparison("Sorting comparison");
        window.pack();
        window.setVisible(true);
    }
}
