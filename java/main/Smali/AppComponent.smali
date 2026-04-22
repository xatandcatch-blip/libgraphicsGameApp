.class public Ljava/main/Smali/AppComponent;
.super Ljava/lang/Object;

.method public static enterCloset()V
    .registers 2
    const/4 v0, 0x1
    const-string v1, "save.rune" # This saves to your current Termux folder
    
    # Call the native hide and save logic
    invoke-static {v0, v1}, Ljava/graphics/PlayerEngine;->setHiding(ZLjava/lang/String;)V
    return-void
.end method
