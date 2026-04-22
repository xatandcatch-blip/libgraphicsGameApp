package java.main;

import android.app.Activity;
import android.os.Bundle;
import java.graphics.PlayerEngine;

public class MainMenuActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // In a real build, you'd setContentView(R.layout.main_menu)
    }

    public void onStartGame() {
        // Logic to transition to the Mansion
    }

    public void setQuality(int level) {
        PlayerEngine.setGraphicsQuality(level);
    }
}
