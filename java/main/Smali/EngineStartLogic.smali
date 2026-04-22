.class public Ljava/main/Smali/EngineStartLogic;
.super Ljava/lang/Object;

.method public static native processAiPath()V
.end method

.method public static handleTick(Landroid/app/Activity;)V
    .registers 2
    # Update AI Navigation
    invoke-static {}, Ljava/main/Smali/EngineStartLogic;->processAiPath()V
    
    # Check if dead
    invoke-static {}, Ljava/graphics/PlayerEngine;->checkDeathStatus()Z
    move-result v0
    if-eqz v0, :cond_8
    return-void
    :cond_8
    return-void
.end method
