package hw;

public class RandomCharacter {

	public static char getRandomCharacter(char char1, char char2) {

		return (char) (char1 + Math.random() * (char2 - char1 + 1));

	}

	public static char getRandomLowCharacter() {
		return getRandomCharacter('a', 'z');
	}

	public static char getRandomUpperCharacter() {
		return getRandomCharacter('A', 'Z');
	}
	
	public static char getRandomDigitCharacter() {
		return getRandomCharacter('0', '9');
	}
	
	
}
