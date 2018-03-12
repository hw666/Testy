package hw;

public class test5 {
	public static void main(String[] args) {

	/*	String r1 = "welcome to java";
		String r2 = new String("welcome to java");
		String r3 = "welcome to java";
		
		System.out.println("r1 == r2?"+ (r1==r2));
		System.out.println("r1 == r3?"+ (r1==r3));
		System.out.println("r1 == r2?"+ (r1.equals(r2)));
		System.out.println("r1 == r3?"+ (r1.equals(r3)));
		
		String s1 = "abf";
		String s2 = "abd";
	
		System.out.println("s1 > s2? "+ s1.compareTo(s2));
	*/
		
	/*	String s1 = "abf";
		String s2 = "abd";
		
		String s3 = s1.concat(s2);
		
		System.out.println(s3);
		System.out.println(s3.charAt(5)+" "+s3.length());
		
		System.out.println(s3.substring(1, 4));
		
		String s4 = "434  2sd  sd";
		System.out.println(s4.trim());
		
		System.out.println(s4.trim().replace('4', '#'));
		
		System.out.println(s4.replaceAll("4", "dddd"));
		
		String[] s = s4.split("\\s+");
		for(String l: s) {
			System.out.println(l);
		}
		
		*/
		
	/*	String str1 = "java is fun!";
		String str2 = "javascript is fun!";
		String str3 = "java  is powerful!";
		
		System.out.println(str1.matches("java is fun!"));
		System.out.println(str1.matches("java"));
		System.out.println(str1.matches("java.*"));
		
		System.out.println(str2.matches("java.*"));
		
		System.out.println(str3.matches("java.*"));
		*/
		
	/*	String str4 = "a+b#$c".replaceAll("[+#$]", "TTT");
		System.out.println(str4);
		
		String[] str5 = "java,C?C#,C++".split("[.,:;?]");
	    for(String s: str5) {
		
	    	System.out.println(s);
	    }
		
	    char[] ch = "java".toCharArray();
	    
	    for(char c: ch) {
			
	    	System.out.println(c);
	    }
	    
	    System.out.println(String.valueOf(ch));
			    
	    System.out.println(Integer.parseInt("123"));
	    
	    */
		
		StringBuilder strbu = new StringBuilder();
		strbu.append("welcone");
		strbu.append(" ");
		strbu.append("to");
		strbu.append(" java");
		
		strbu.insert(11, "HTML and ");
		
		strbu.delete(8, 11);
		strbu.deleteCharAt(8);
		
		strbu.reverse();
		
		System.out.println(strbu.toString());
		
		StringBuffer strbuf =new StringBuffer();
		
		strbuf.append("hello");
		System.out.println(strbuf.length());
		
		System.out.println();
		
	}
}
