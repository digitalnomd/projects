//Author: Robert Grossman
//Description: Demonstrates a dynamic programming method for determining
//whether or not a number is a fibonacci number.

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class FibonacciValidator{
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static int previous = 0;
    static int current = 1;
    
    public static void sequence(int test, HashSet<Integer> set) {
        //keep growing the sequence until the set is big enough
        while (current < test) {
            int temp = current;
            current = current + previous;
            previous = temp;
            //add the new numbers to the set along the way
            set.add(previous);
            set.add(current);
        }
    }
    
    public static void main(String[] args) throws IOException, ParseException{
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        int cases = Integer.parseInt(in.readLine());
        
        //use a buffer so we don't do extra work and add the first 2 numbers
        HashSet<Integer> fiboNums = new HashSet<Integer>(100000);
        fiboNums.add(0);
        fiboNums.add(1);
        
        NumberFormat format = NumberFormat.getIntegerInstance( );
        
        for (int i = 1; i <= cases; i++) {
            Number number = format.parse(in.readLine());
            int test = number.intValue();
            
            //make sure the fibonacci set of numbers is big enough first
            sequence(test, fiboNums);
            
            //then test if the number is in the set
            if (fiboNums.contains(test)) {
                System.out.println("IsFibo");
            }
            else{
                System.out.println("IsNotFibo");
            }
        }
	
	in.close();
    }

    
}
