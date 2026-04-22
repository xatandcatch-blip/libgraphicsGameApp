.class public Ljava/main/Smali/EngineStartLogic;
.super Ljava/lang/Object;

# Native method to generate randomized mansion layout
.method public static native generateChunk(I)I
.end method

# Tick handler with death check
.method public static handleTick(Landroid/app/Activity;)V
    .registers 2
    invoke-static {}, Ljava/graphics/PlayerEngine;->checkDeathStatus()Z
    move-result v0
    if-eqz v0, :cond_8
    return-void
    :cond_8
    return-void
.end method
