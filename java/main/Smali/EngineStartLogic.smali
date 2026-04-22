.class public Ljava/main/Smali/EngineStartLogic;
.super Ljava/lang/Object;

# Native bridge for item collection
.method public static native pickupItem(I)V
.end method

.method public static native processTick()V
.end method

.method public static handleTick(Landroid/app/Activity;)V
    .registers 1
    invoke-static {}, Ljava/main/Smali/EngineStartLogic;->processTick()V
    return-void
.end method
