package java.main;

public class GameLogic {
    public static float getPanicIntensity(int aiState, float sanity) {
        // aiState 2 is CHASING
        if (aiState == 2) return 1.0f + (100.0f - sanity) / 50.0f;
        return 0.0f;
    }

    public static float getBatteryDrainRate(float distance) {
        return (distance < 4.0f) ? 0.15f : 0.01f;
    }
}
