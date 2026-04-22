package java.main;

public class GameLogic {
    private static boolean isHiding = false;

    public static void setHidingState(boolean state) {
        isHiding = state;
    }

    public static float getHeartbeatRate(float distance) {
        if (distance > 20.0f) return 1.0f; // Normal
        if (distance < 2.0f) return 4.0f;  // Extreme Panic
        
        // Linear scale: closer = faster
        return 1.0f + (20.0f - distance) / 5.0f;
    }

    public static boolean canEntitySeePlayer(float distance) {
        if (isHiding) return distance < 1.5f;
        return distance < 15.0f;
    }
}
