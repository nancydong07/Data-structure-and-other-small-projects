package hw5.graphs;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.ListIterator;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

class Graph<T> {

    int numVertices;
    int numOfEdges;
    HashMap<T, Vertex<T>> values = new HashMap<>();

    public Graph() {

    }

    public Graph(String filename) {
        //   Graph <String> edges = new Graph<String>("graph.dot");
        try {
            File f = new File("graph.dot");
            Scanner in = new Scanner(f);
            String[] take;
            String current = in.nextLine();
            while (in.hasNextLine()) {
                current = in.nextLine();
                if (current.startsWith("}")) {
                    break;
                }
                take = current.split("->");

                String s = take[0].trim();
                String s1 = take[1].trim();
                this.addEdge((T) s, (T) s1);

            }
        } catch (FileNotFoundException ex) {
            System.out.println("file not found");
        }
    }

    /*This method takes in two generic types. It uses a hashmap to check 
     *if the two elements exist; if the element does not exist, add the 
     *element into the map as a key which represents a vertex. Then, 
     *add the second element to the list of the key represented by the first
     *element. This method has O(1) runtime. 
     *Parameters- x: the vertex with the outgoing edge.
     y: the vertex with the incoming edge from x.
     */
    public void addEdge(T x, T y) {
        
        if (!values.containsKey(x)) { // If the first vertex is not in the keyset,
            values.put(x, new Vertex(x)); // add the vertex into the keyset which will
            numVertices++; // be holding Vertex values.
        }
        if (!values.containsKey(y)) { // If the second vertex is not in the keyset, 
            values.put(y, new Vertex(x)); // add the vertex into the keyset which will
            numVertices++; // be holding Vertex values. 
        }
        if(!isEdge(x,y)){ //Check if the edge already exists. 
        values.get(x).addNeighbors(y); // Add the second vertex to the first vertex's list 
        numOfEdges++; }// of neighbors. 
    }

    /*This method takes in 2 generic vertices. It uses a ListIterator to iterate
     *through the neighbors of the first vertex until it reaches the second vertex. It 
     *removes the edge from the first to second vertex by removing the second vertex from
     *the list of neighbors. This method is done in O(n) runtime. 
     *Parameters- x: the vertex that has the outgoing edge.
     y: the vertex that has the incoming edge from x. It is the vertex to be 
     remove from x's list. 
     */
    public void removeEdge(T x, T y) throws NoSuchElementException {
        boolean contain = false; // Checks if the second vertex is a neighbor of the first vertex.
        if (!values.containsKey(x) || !values.containsKey(y)) { // If either vertices do not exist, throw exception.
            throw new NoSuchElementException();
        }

        ListIterator<T> temp = values.get(x).getNeighbors().listIterator(); // To iterate through the first vertex's neighbor.
        while (temp.hasNext()) {
            if (temp.next() == y) { // remove the vertex if it's equal to the second vertex.
                temp.remove();
                numOfEdges--;
                contain = true; // Then the second vertex was in the the first vertex's neighbor list.
                break;
            }
        }
        if (contain == false) { //If the second vertex was not in the neighbor list, then throw exception.
            throw new NoSuchElementException();
        }

    }

    /*This method takes in two vertices of generic type and uses ListIterator to iterate through
     *the first vertex's neighbor list. It returns true if the second vertex exist in that list i.e 
     *the first vertex was connected to the second. 
     *Parameters- x: the vertex with the outgoing edge.
     y: the vertex with the incoming edge from x.
     *Return- true if the first vertex has an edge going to the second vertex. False otherwise.
     */
    public boolean isEdge(T x, T y) throws NoSuchElementException {
        if (!values.containsKey(x) || !values.containsKey(y)) {
            throw new NoSuchElementException();
        }
        boolean exist = false; // Checks if y exist in x's neighbor list.
        ListIterator<T> temp = values.get(x).getNeighbors().listIterator();// Iterates through x's neighbor.
        while (temp.hasNext()) {
            if (temp.next() == y) {
                exist = true;
                break;
            }
        }
        return exist;
    }
    /*This method takes in one vertex of generic type and returns 
     *its neighbors.
     *Parameter - x: the vertex whose neighbors will be returned.
     *Returns - a linked list of the vertex's neighbors.
     */

    public LinkedList<T> neighbors(T x) throws NoSuchElementException {
        if (!values.containsKey(x)) {
            throw new NoSuchElementException();
        }
        return values.get(x).getNeighbors();
    }
    /*This method returns the number of vertices that exist in the graph. 
     *Returns - the number of vertices. 
     */

    public int numVertices() {
        return numVertices;
    }
    /*This method returns the total number of edges that exist in the graph. 
     *Returns - the number of edges. 
     */

    public int numEdges() {
        return numOfEdges;
    }
    /*This method takes in a vertex of a generic type and removes that vertex
     *from the graph along with all incomng and outgoing edges attached to that 
     *vertex. It uses Iterator to iterate through the keys and then uses ListIterator
     *to iterate through each list and remove that target vertex from all the neighbors 
     *list. This is done in O(number of vertices + lenght of each list) runtime.
     *Parameter - x: the vertex to be removed along with any edges connected to it. 
     */

    public void removeVertex(T x) throws NoSuchElementException {
        if (!values.containsKey(x)) {
            throw new NoSuchElementException();
        }
        numOfEdges -= values.get(x).getNeighbors().size(); // reduce the number of edges by the size of x's neighbor list. 
        values.remove(x);
        numVertices--;
        Iterator<T> map = values.keySet().iterator();
        while (map.hasNext()) {
            T key = map.next();
            ListIterator<T> temp = values.get(key).getNeighbors().listIterator();// Iterates through the given key's neighbors list. 
            while (temp.hasNext()) { // Remove the value from the neighbors list if it equals x. 
                if (temp.next() == x) {
                    temp.remove();
                    numOfEdges--;
                }
            }
        }
    }
    /*This method takes in a file name and writes to that file. It 
     *checks the adjacency each vertex in the graph and prints the 
     *edge list. 
     *Paramter - filename: the file that the method writes to.
    */
    public void toDotFile(String filename) {
        File f = new File("newGraph.dot");
        try {
            FileWriter fw = new FileWriter(f);
            PrintWriter pw = new PrintWriter(fw);
            Iterator<T> map = values.keySet().iterator();
            T key;
            pw.println("Diagraph {");
            while (map.hasNext()) { // Iterate through the keys and for each key, get its neighbors.
                key = map.next();
                ListIterator<T> temp = values.get(key).getNeighbors().listIterator();
                while (temp.hasNext()) { //For that particular key, print the edge list with all its neighbors.
                    pw.println("    " + key + "->" + temp.next());
                }
            }
            pw.println("}");
            pw.close();

        } catch (IOException e) {
            System.out.println("File not found");
        }

    }
    /*This method is called by depthFirstSearch and it takes in a generic 
     *type for vertex and a HashMap with a generic key and boolean values.
     *It uses a linked list to store the neighbors and a ListIterator to 
     *to traverse the list. It prints out the vertex label in depth first order 
     *by recursively finding the next neighbors list to traverse. 
     *Parameter - x: the key whose neighbors list will be traverse.
     marked: if the vertex i.e. key is printed, then its value
     becomes true. 
     */

    public void dfsHelper(T x, HashMap<T, Boolean> marked) {
        LinkedList<T> connections = values.get(x).getNeighbors();
        marked.replace(x, true); // Since the vertex x will be visited, its value becomes true.
        T nextNeighbor;
        ListIterator<T> temp = connections.listIterator();
        while (temp.hasNext()) {
            nextNeighbor = temp.next(); // set nextNeighbor to the next value in x's neighbors list.  
            if (!marked.get(nextNeighbor)) { // if nextNeighbor has not been visited, visit it and 
                System.out.println(nextNeighbor); // and then make a recursive call to get nextNeighbor's 
                dfsHelper(nextNeighbor, marked); // neighbors list. 
            }
        }
    }
    /*This method takes in a generic type for the vertex which serves as the 
     *starting point for the depth first search. It makes a hashmap to keep 
     *to keep track the vertex visited and and initializes all the values 
     *to false. It passes this to dfsHelper method.
     *Parameter - x: the starting vertex.
     */

    public void depthFirstSearch(T x) throws NoSuchElementException {
        if (!values.containsKey(x)) {
            throw new NoSuchElementException();
        }
        HashMap<T, Boolean> marked = new HashMap<T, Boolean>();
        Iterator<T> map = values.keySet().iterator();
        T key;
        while (map.hasNext()) {
            key = map.next();
            marked.put(key, false);
        }
        System.out.println(x); // Since dfsHelper method starts at its neighbors, it 
        dfsHelper(x, marked); // skips the first vertex to be visited.

    }
    /*This method takes in a generic type for the vertex and prints the vertex in 
     *breadth first order. It uses a hashmap to keep track of the vertices visited
     *and a queue to store all the neighbors. 
     *Parameter - x: the starting vertex. 
     */

    public void breadthFirstSearch(T x) throws NoSuchElementException {
        if (!values.containsKey(x)) {
            throw new NoSuchElementException();
        }
        HashMap<T, Boolean> marked = new HashMap<T, Boolean>();
        Queue<T> neighbors = new Queue<T>();
        LinkedList<T> connections = values.get(x).getNeighbors();
        Iterator<T> map = values.keySet().iterator();
        T key;
        while (map.hasNext()) { //Initialize the hashmap values to false.
            key = map.next();
            marked.put(key, false);
        }
        marked.replace(x, true); //Set the starting vertex value to true.
        neighbors.enqueue(x);
        T vertex;
        ListIterator<T> temp = connections.listIterator();//To traverse the given vertex's neighbors list.
        T nextNeighbor;
        while (!neighbors.isEmpty()) { // while the queue isn't empty
            vertex = neighbors.dequeue(); // current vertex becomes the 
            System.out.println(vertex); // the first vertex that was added to the queue.
            connections = values.get(vertex).getNeighbors(); //Get the neighbors of the current 
            temp = connections.listIterator(); // vertex. 
            while (temp.hasNext()) { //  While there is still more neighbors of that vertex, 
                nextNeighbor = temp.next();
                if (!marked.get(nextNeighbor)) { // if the vertex has not been visited, 
                    marked.replace(nextNeighbor, true);
                    neighbors.enqueue(nextNeighbor);// add the neighbor/vertex into the queue.
                }
            }
        }

    }
    /*This method takes in a generic type for vertex and outputs the vertices 
     *in depth first order starting at the given vertex. It uses a hashmap to 
     *keep track of the visited vertices, a stack to store and print the neighbors
     *in the correct order, and a linked list to obtain the current vertex's neighbors 
     *list. 
     *Parameter - x: the starting vertex. 
     */

    public void depthFirstSearchIterative(T x) throws NoSuchElementException {
        if (!values.containsKey(x)) {
            throw new NoSuchElementException();
        }
        HashMap<T, Boolean> marked = new HashMap<T, Boolean>();
        Stack<T> neighbors = new Stack<T>();
        LinkedList<T> connections = values.get(x).getNeighbors();
        Iterator<T> map = values.keySet().iterator();
        T key;
        while (map.hasNext()) { // Initialize all values for each key to false.
            key = map.next();
            marked.put(key, false);
        }
        neighbors.push(x); // push the vertex into the stack.
        T vertex;
        ListIterator<T> temp = connections.listIterator();
        T nextNeighbor;
        while (!neighbors.isEmpty()) { // While the stack is not empty,
            vertex = neighbors.pop(); // set vertex equal to the top value in stack.
            if (!marked.get(vertex)) { // If the vertex has not been visited, print it.
                System.out.println(vertex);
                marked.replace(vertex, true);
            }
            connections = values.get(vertex).getNeighbors(); //Get the neighbors of that visited vertex.
            temp = connections.listIterator();
            while (temp.hasNext()) { //While there are still vertices in the neighbors list,
                nextNeighbor = temp.next();
                if (!marked.get(nextNeighbor)) { // If the vertex has not been visited, push the vertex into the stack.
                    neighbors.push(nextNeighbor);

                }
            }

        }
    }

    public HashMap<T, Vertex<T>> getValues() {
        return values;
    }
    
    /*This method prints out the hashmap's key and its
     *associated linked list.
    */
    public void hashmapString(){
        Iterator<T> map = values.keySet().iterator();
        T key;
        while (map.hasNext()){
            key=map.next();
            LinkedList temp = values.get(key).getNeighbors();
            System.out.println(key + "->" +temp);
          //  System.out.println(key + "->" +temp);
        } 
       
    }

    public static void main(String[] args) {
        //  Graph<Integer> test = new Graph<Integer>();

        /*    test.addEdge(5, 7);
         test.addEdge(5, 8);
         test.addEdge(5, 9);

         System.out.println("hi " + test.neighbors(5));
         test.removeEdge(5, 7);
         System.out.println("plze " + test.getValues().get(5).getNeighbors());
         System.out.println("is edge " + test.isEdge(5, 9));
         System.out.println("num " + test.numVertices());
         System.out.println("edges " + test.numEdges());*/
        Graph<String> test1 = new Graph<String>();
        test1.addEdge("a", "b");
        test1.addEdge("a", "b");
        test1.addEdge("a", "a");
        test1.addEdge("a", "c");
        test1.addEdge("b", "d");
        test1.addEdge("b", "e");
        test1.addEdge("e", "h");
        test1.addEdge("c", "f");
        test1.addEdge("c", "g");
        test1.addEdge("f", "k");
        test1.toDotFile("newGraph.dot");
        System.out.println("test 1 ed " + test1.numEdges());
        test1.depthFirstSearch("a");
        //      test1.removeVertex("a");
    /*    test1.addEdge(3, 10);
         test1.addEdge(3, 1);
         test1.addEdge(3, 6);
         test1.addEdge(1, 6);
         test1.addEdge(6, 10);
         test1.addEdge(10, 5);
         test1.addEdge(5, 7);
         test1.addEdge(5, 8);
         test1.addEdge(10, 7);
         test1.addEdge(10, 3);*/
        /*   test1.addEdge(3,7);
         test1.addEdge(3,5);
         test1.addEdge(7,4);
         test1.addEdge(7,8);
         test1.addEdge(7,10);
         test1.addEdge(5,6);
         test1.addEdge(5, 9);
         test1.addEdge(3,9);
         test1.addEdge(6,9);*/
        System.out.println("a neighbors " + test1.neighbors("a"));
        //   System.out.println("labels " + test1.getValues().get(1).getLabel());
        //   System.out.println("test " + test1.neighbors(3));
        //  System.out.println("num " + test1.numVertices());
        //  System.out.println("edges " + test1.numEdges());
        Graph<String> x = new Graph<String>("graph.dot");

        System.out.println("num of v " + x.numVertices());
        System.out.println("num of ed " + x.numEdges());
        x.hashmapString();
        //   x.toString("C");
        
    }
}
