package java.main;

public class GameLogic {
    private static boolean isHiding = false;

    public static void setHidingState(boolean state) {
        isHiding = state;
    }

    public static boolean canEntitySeePlayer(float distance) {
        // If hiding, the entity can only see you if it's practically touching you
        if (isHiding) {
            return distance < 1.5f;
        }
        // Otherwise, standard line-of-sight distance
        return distance < 15.0f;
    }
}
