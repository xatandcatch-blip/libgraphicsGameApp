package java.graphics;

public class PlayerEngine {
    public static native void saveGame(String path);
    public static native void loadGame(String path);
    public static native float getHeartbeatRate();
    public static native void drinkSoda();
}
