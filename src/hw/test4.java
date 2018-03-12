package hw;

import java.util.Scanner;

public class test4 {
public static void main(String[] args) {
	@SuppressWarnings("resource")
	Scanner input = new Scanner(System.in);
	double[][] arr = new double[8][2];

	for(int row =0;row < arr.length;row++) {
		for(int col = 0;col<arr[0].length;col++) {
			arr[row][col] = input.nextDouble();
		}
	}
	
	double mindis = distence(arr[0][0],arr[0][1],arr[1][0],arr[1][1]);
	int row1=0, row2=0;
	
	for(int i=0;i< arr.length;i++) {
		
		for(int j=i+1;j<arr.length-1;j++) {
			double currentdis = distence(arr[i][0],arr[i][1],arr[j][0],arr[j][1]);
			
			if(mindis > currentdis) {
				mindis = currentdis;
				row1 = i;
				row2 = j;
			}
		}
	}
	
	System.out.println("The min distence is "+ mindis+ ", these two point are ("+arr[row1][0]+","+arr[row1][1]+") , ("+arr[row2][0]+","+arr[row2][1] +")");
	
}

	public static double distence(double x1, double x2, double x3, double x4) {
		double result = 0;
		result = Math.sqrt((x1 - x3) * (x1 - x3) + (x2 - x4) * (x2 - x4));
		return result;
	}
}