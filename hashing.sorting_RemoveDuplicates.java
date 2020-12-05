package hw4.hashing.sorting;

import java.util.LinkedList;
import java.util.ListIterator;
import java.util.HashMap;

class RemoveDuplicates {
    /* This method takes in a linked list of integers and removes duplicate values from the list. It uses a hashmap 
     *to access elements in O(1) time with O(n) space. The hashmap checks if the element is already
     *in the map, and if it is, it will be removed from the list using the list iterator as tranversal.
     *Parameters: A list of integers 
    */
    public static void removeDuplicates(LinkedList<Integer> numbers) {
        ListIterator <Integer> ll2 = numbers.listIterator(); 
        HashMap data = new HashMap();
        while (ll2.hasNext()) { //While the list still has elements
            Integer x=ll2.next();//Store the value after next interation
            if (!data.containsKey(x)) { //Check if the hash map already has the data
                data.put(x, null); //If no, then enter the key
            } else { //If yes, goes to the next value and remove the previous value.
                ll2.remove();
            }

        }

    }

    public static void main(String[] args) {
        // EXAMPLE TEST
      /*  LinkedList<Integer> list = new LinkedList<Integer>();
        list.addLast(0);
        list.addLast(3);
        list.addLast(5);
        list.addLast(2);
        list.addLast(2);
        list.addLast(0);
        list.addLast(3);
        list.addLast(10);
        list.addLast(5);
        list.addLast(0);

            removeDuplicates(list);*/
        
    }
}
