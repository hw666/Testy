package hw;

public class test3 {

	public static void main(String[] args) {
		

		for(int k=2, flag=0; flag < 100; k++) {
			if(isPrime(k) && isHuiwen(k)) {
				
				flag ++;
				if(flag % 10 ==0) {
					System.out.printf("%8d",k);
					System.out.println();
				}else {
					System.out.printf("%12d",k);
				}

			}
		}

	}
	

	//判断素数
	public static boolean isPrime(int num) {  
		int temp = (int) Math.sqrt(num);
		
		for(int i = 2;i<=temp;i++) {
			if(num % i ==0) {
				return false;
			}
		}
		
		return true;
	}
	
	//判断回文数
	public static boolean isHuiwen(int num) {
		String str = String.valueOf(num);
		
		for(int i=0;i<str.length()/2;i++) {
			if(str.charAt(i) != str.charAt(str.length()-i-1)) {
				return false;
			}
		}
		
		return true;
	}
	
	
}
