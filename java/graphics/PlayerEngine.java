package java.graphics;

public class PlayerEngine {
    public static native void updatePlayerPos(float x, float y, float z);
    public static native boolean isColliding();
    // New Native Trigger for Consumables
    public static native void drinkSoda();
}
