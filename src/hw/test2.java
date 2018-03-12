package hw;

import java.util.Arrays;
import java.util.Scanner;

public class test2 {
	public static void main(String[] args) {

	/*	Scanner input = new Scanner(System.in);
		
		int num = (int)(Math.random()*100);
		
		System.out.println("Guess a number from 0 to 100");
		
		
		while(true) {
			System.out.print("Guess a number: ");
			int guessNum = input.nextInt();
			
			if(guessNum == num) {
				System.out.println("Yes, the number is "+ num);
				break;
			}
			else if(guessNum > num) {
				System.out.println("The num is too high");
			}
			else {
				System.out.println("The num is too low");
			}	
		}
		
	*/
		
	/*	Scanner input =new Scanner(System.in);
		
		System.out.print("Input two different numbers: ");
		int first = input.nextInt();
		int second = input.nextInt();
		
		int temp = first;
		
		if(temp > second) {
			 temp = second;
		}
		
		while(true) {
			if(first % temp ==0 && second % temp ==0) {
				System.out.println("The number is "+ temp);
				break;
			}
			
			temp--;
		}
	*/
		
	/*	Scanner input =new Scanner(System.in);
		System.out.print("INput line : ");
		int line = input.nextInt();
		
		for(int i=1;i<=line;i++) {
			for(int j=0;j<(line-i)*2;j++) {
				System.out.print(" ");
			}
			
			for(int k=0;k<i;k++) {
				System.out.print(i-k+" ");
			}
			
			for(int l=1;l<i;l++) {
				System.out.print(l+1+" ");
			}
			
			System.out.println();
		}
		
	*/
		
	/*	int line = 8;
		int k;
		
		for(int i=1;i<=line;i++) {
			for(int j=0;j<(line-i)*4;j++) {
				System.out.print(" ");
			}
			
			for( k=1;k<Math.pow(2, i);k=k*2) {
				System.out.printf("%4d",k);
			}
			
			for(int l=k/4;l>=1;l=l/2) {
				System.out.printf("%4d",l);
			}
			System.out.println();
			
		}
		*/
		
	/*	int n = 50000;
		double first = 0;
		double second = 0;
		
		for(int i=n;i>=1;i--) {
			first = first + (1.0/i);
		}
		
		for(int j=1;j<=n;j++) {
			second = second + (1.0/j);
		}
		
		System.out.println("First result: "+first);
		System.out.println("Second result: "+second);
		
 */
	/*	Scanner input=new Scanner(System.in);
		
		double[] list = new double[10];

		for(int i=0;i<list.length;i++) {
			list[i]=input.nextDouble();
		}
		
		
		for(double l:list) {
			System.out.println(l);
		}
		
	*/
	/*	Scanner input=new Scanner(System.in);
		int[] array = new int[10];
		
		System.out.print("Input ten numbers: ");
		for(int i =0 ;i<array.length;i++) {
			array[i]=input.nextInt();
		}
		
		System.out.print("Input need seach number: ");
		int seach = input.nextInt();
		
		
		
	    System.out.println(binarySeach(array, seach));
		
		*/
		
	/*	//Ñ¡ÔñÅÅÐò
		int[] list = {2,3,5,8,1,5,6,0,7,56};
		int len = list.length;
		
		int temp,min,flag=0;
		
		for(int i=0;i<len-1;i++) {
			min = list[i];
			flag = i;
			for(int j=i+1;j<len;j++) {
				if(min > list[j]) {
					min = list[j];
					flag = j;
				}
			}
			
			list[flag] = list[i];
			list[i] = min;
		}

		for(int l: list) {
			System.out.print(l+",");
		}
    */
		
	/*	int[] list = {2,5,3,8,1,5,6,0,7,56};
		int len = list.length;
		
		int current = 0;
		
		for(int i=1;i<len;i++) {
			current = list[i];
			
			for(int j=i-1;j>=0;j--) {
				if(current < list[j]) {
					list[j+1] = list[j];
					list[j] = current;
				}
			}
		}
		
		for(int l: list) {
			System.out.print(l+",");
		}
	*/
		
	/*	int[] list = {2,5,3,8,1,5,6,0,7,56};
		int len = list.length;
		
		for(int i=0;i<len;i++) {
			for(int j=0;j<len-i-1;j++) {
				if(list[j] > list[j+1]) {
					int temp = list[j];
					list[j] = list[j+1];
					list[j+1] = temp;
				}
			}
		}
		
		for(int l: list) {
			System.out.print(l+",");
		}
		*/
		
		int[] list = {2,5,3,8,1,5,6,0,7,56};
		
		Arrays.sort(list);
		
		for(int l: list) {
			System.out.print(l+",");
		}
		
		System.out.println(Arrays.binarySearch(list, 9));
		
	}
	
	public static int binarySeach(int[] arr, int key) {
		
		int low = 0;
		int high = arr.length-1;
		
		while(high>=low) {
			int middle = (low + high)/2;
			if(key == arr[middle]) {
				return key;
			}
			else if(key < arr[middle]){
				high = middle-1;
			}
			else {
				low = middle+1;
			}
		}
		
		return -low-1;
		
	}
	
	
		
		
}
