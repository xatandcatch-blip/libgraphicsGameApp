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

.method public static onConfirmDelete()V
    .registers 1
    const-string v0, "save.rune"
    # The 'Warning' logic happens in the Java/UI layer before calling this
    invoke-static {v0}, Ljava/graphics/PlayerEngine;->deleteSaveFile(Ljava/lang/String;)Z
    return-void
.end method
