import java.util.Scanner;

public class HelloWorld {
	public native void reportEvent(String message); // native method

	static // static initializer code
	{
		System.loadLibrary("CLibHelloWorld");
	}

	public static void main(String[] args) {

		System.out.println("Please, type a message to log:");
		System.out.println("Please, type 'exit' to close the program.");

		HelloWorld hw = new HelloWorld();
		Scanner scanIn = new Scanner(System.in);
		String message = scanIn.nextLine();

		while (!message.equals("exit")) {
			hw.reportEvent(message);
			message = scanIn.nextLine();
		}
	}
}
