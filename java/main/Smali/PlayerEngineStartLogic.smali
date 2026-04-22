.class public Ljava/main/Smali/PlayerEngineStartLogic;
.super Ljava/lang/Object;

# Native call to get distance-based intensity
.method public static native getHeartbeatIntensity()I
.end method

.method public static triggerHaptic(Landroid/content/Context;)V
    .registers 3
    invoke-static {}, Ljava/main/Smali/PlayerEngineStartLogic;->getHeartbeatIntensity()I
    move-result v0
    
    if-lez v0, :cond_10
    
    const-string v1, "vibrator"
    invoke-virtual {p0, v1}, Landroid/content/Context;->getSystemService(Ljava/lang/String;)Ljava/lang/Object;
    move-result-object p0
    check-cast p0, Landroid/os/Vibrator;
    
    # Vibrate for 'v0' milliseconds (the intensity value)
    int-to-long v0, v0
    invoke-virtual {p0, v0, v1}, Landroid/os/Vibrator;->vibrate(J)V

    :cond_10
    return-void
.end method
