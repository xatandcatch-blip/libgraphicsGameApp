package java.graphics;

public class PlayerEngine {
    public static native void updatePlayerPos(float x, float y, float z);
    public static native boolean isColliding();
    public static native void drinkSoda();
    public static native void toggleNightVision(boolean active);
    // New: Audio Pulse Rate
    public static native float getHeartbeatRate();
}
