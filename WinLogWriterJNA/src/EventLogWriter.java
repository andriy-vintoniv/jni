import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import com.sun.jna.win32.StdCallLibrary;
import com.sun.jna.win32.W32APIOptions;

public class EventLogWriter {

	public interface CLibrary extends Library {
		CLibrary INSTANCE = (CLibrary) Native.loadLibrary(
				(Platform.isWindows() ? "msvcrt" : "c"), CLibrary.class);

		void printf(String format, Object... args);
	}

	public interface Advapi32 extends StdCallLibrary {
		Advapi32 INSTANCE = (Advapi32) Native.loadLibrary("Advapi32",
				Advapi32.class, W32APIOptions.UNICODE_OPTIONS);

		Pointer RegisterEventSource(String lpUNCServerName, String lpSourceName);

		class PSID extends Structure {

			@Override
			protected List getFieldOrder() {
				// TODO Auto-generated method stub
				return null;
			}

		}

		boolean ReportEvent(Pointer hEventLog, short wType, short wCategory,
				int dwEventID, Pointer lpUserSid, short wNumStrings,
				int dwDataSize, String[] lpStrings, Pointer lpRawData);

	}

	public static void main(String[] args) {
		CLibrary.INSTANCE.printf("Hello %s", "Oleh");

		Pointer eventSource = Advapi32.INSTANCE.RegisterEventSource(null,
				"messageProvider");

		String[] message = new String[] { "JNA event" };

		Advapi32.INSTANCE.ReportEvent(eventSource, (short) 4, (short) 3, 0,
				null, (short) 1, 0, message, null);
	}
}
