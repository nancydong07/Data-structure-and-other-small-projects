
package hw5.graphs;

import java.util.LinkedList;

class Vertex<T> {
    private T label;
    private double weight;
    private LinkedList<T> neighbors;
    
    public Vertex(T label) {
        setLabel(label);
        setNeighbors(new LinkedList<T>());
        setWeight(1);
    }

    public T getLabel() {
        return label;
    }

    public void setLabel(T label) {
        this.label = label;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }
    
    /*This method takes in a vertex of generic type and
     *adds that vertex to the end of the neighbors list.
     *Parameter- x: the vertex to be added.
    */
    public void addNeighbors(T x){
        neighbors.addLast(x);
    }
    public LinkedList<T> getNeighbors() {
        return neighbors;
    }

  
    public void setNeighbors(LinkedList<T> neighbors) {
        this.neighbors = neighbors;
    }

}