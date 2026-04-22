package java.main;

public class GameLogic {
    private static boolean isHiding = false;
    private static boolean isDead = false;

    public static void setHidingState(boolean state) {
        isHiding = state;
    }

    public static void triggerDeath() {
        isDead = true;
    }

    public static boolean checkDeathStatus() {
        return isDead;
    }

    public static float getBatteryDrainRate(float distance) {
        if (distance > 5.0f) return 0.01f;
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
