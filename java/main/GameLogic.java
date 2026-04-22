package java.main;

public class GameLogic {
    private static boolean isHiding = false;

    public static void setHidingState(boolean state) {
        isHiding = state;
    }

    // Flashlight flickers and drains when the Entity is within 5 meters
    public static float getBatteryDrainRate(float distance) {
        if (distance > 5.0f) return 0.01f; // Standard drain
        
        // Rapid drain when the monster is breathing down your neck
        return 0.01f + (5.0f - distance) / 10.0f;
    }

    public static float getHeartbeatRate(float distance) {
        if (distance > 20.0f) return 1.0f;
        if (distance < 2.0f) return 4.0f;
        return 1.0f + (20.0f - distance) / 5.0f;
    }

    public static boolean canEntitySeePlayer(float distance) {
        if (isHiding) return distance < 1.5f;
        return distance < 15.0f;
    }
}
