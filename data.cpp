#include <jni.h>
#include <stdint.h>
#include <math.h>

extern "C" {
    // Shared State
    float P_X = 0.0f, P_Z = 0.0f, E_X = 5.0f, E_Z = 5.0f;
    float HEALTH = 100.0f, STAMINA = 100.0f, BATTERY = 100.0f, SANITY = 100.0f;
    bool IS_DEAD = false;

    // JNI Mapped: com.logic.CollisionLogic.isHitboxTrigger()
    JNIEXPORT jboolean JNICALL Java_com_logic_CollisionLogic_isHitboxTrigger(JNIEnv* env, jclass clazz) {
        float dx = fabsf(P_X - E_X);
        float dz = fabsf(P_Z - E_Z);
        return (dx < 1.2f && dz < 1.2f);
    }

    // JNI Mapped: com.logic.EngineLogic.updateNativeTick(boolean, boolean)
    JNIEXPORT void JNICALL Java_com_logic_EngineLogic_updateNativeTick(JNIEnv* env, jclass clazz, jboolean sprint, jboolean light) {
        if (IS_DEAD) return;
        
        // Restore Battery/Stamina/Sanity logic here...
        if (sprint && STAMINA > 0) STAMINA -= 0.5f;
        if (light && BATTERY > 0) BATTERY -= 0.08f;
        
        if (Java_com_logic_CollisionLogic_isHitboxTrigger(env, clazz)) {
            HEALTH -= 5.0f;
            if (HEALTH <= 0) IS_DEAD = true;
        }
    }
}
