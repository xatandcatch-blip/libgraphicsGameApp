.class public Ljava/main/Smali/MainMenuUI;
.super Ljava/lang/Object;

.method public static handleSettingsClick(I)V
    .registers 1
    # Call JNI to update native graphics state
    invoke-static {p0}, Ljava/graphics/PlayerEngine;->setGraphicsQuality(I)V
    return-void
.end method

.method public static handleStartClick()V
    .registers 0
    # Logic to initialize GameEngine and start the tick
    return-void
.end method
