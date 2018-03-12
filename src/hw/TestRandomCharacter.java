package hw;

public class TestRandomCharacter {
 public static void main(String[] args) {
	 for(int i=1;i<=100;i++) {
		 char ch =RandomCharacter.getRandomUpperCharacter();
		 
		 if(i % 10 == 0) {
			 System.out.println();
		 }
		 
		 System.out.print(ch);
	 }
 }
}
