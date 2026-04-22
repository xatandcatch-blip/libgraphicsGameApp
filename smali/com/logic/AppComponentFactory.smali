.class public Lcom/logic/AppComponentFactory;
.super Ljava/lang/Object;

.method static constructor <clinit>()V
    .registers 1
    const-string v0, "vulkan_core"
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
    return-void
.end method
