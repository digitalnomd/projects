//Author: Robert Grossman
//Description: A solution to the hackerrank problem Sherlock and Watson,
//demonstrating an O(1) method for rotating a list.

import java.io.*;
import java.util.LinkedList;

public class RotatingList{

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    
    static void rotate(LinkedList<Integer> array, int K) {
        for (int i = 0; i < K; i++) {
	    //for each rotation just move the last node to the front
            array.addFirst(array.getLast());
            array.removeLast();
        }
    }
    
    public static void main(String[] args) throws IOException{
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */    
	//first read in and parse the parameters of the problem.
	int N, K, Q;
        String line = in.readLine();
        String[] params = line.split(" ");
        N = Integer.parseInt(params[0]); //size of array
        K = Integer.parseInt(params[1]); //number of rotations
        Q = Integer.parseInt(params[2]); //number of queries
       
	//then read in and parse the array 
        LinkedList<Integer> array = new LinkedList<>();
        String s = in.readLine();
        String[] integers = s.split(" ");
        
        
        for (int i = 0; i < N; i++) {
            array.add(Integer.parseInt(integers[i]));
        }
        
	//rotate the array K times 
        rotate(array, K);
        
        for (int i = 0; i < Q; i++) {
            int element = Integer.parseInt(in.readLine());
	    //output each specific element of the array so that you can check that the rotation worked
            System.out.println(array.get(element));
        }
	
	//close the input stream
	in.close();
        
    }
}
