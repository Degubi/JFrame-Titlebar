package jframetitlebar;

import java.io.*;
import java.nio.file.*;
import javax.swing.*;

/**
 * Utility class used for updating the titlebar theme of a JFrame object<br>
 * Note: These functions only return/apply the correct themes when the JFrame is already visible
 * @author Degubi
 */
public final class JFrameTitlebar {

    static {
        try(var dllInputStream = JFrameTitlebar.class.getResourceAsStream("/JFrameTitlebar.dll")) {
            var dllOutputPath = Path.of(System.getProperty("java.io.tmpdir") + "/JFrameTitlebar.dll");

            Files.copy(dllInputStream, dllOutputPath, StandardCopyOption.REPLACE_EXISTING);
            System.load(dllOutputPath.toAbsolutePath().toString());
        } catch (IOException e) {
            throw new IllegalStateException("Unable to extract JFrameTitlebar.dll!", e);
        }
    }

    public static native boolean isLightMode(JFrame frame);
    public static native boolean isDarkMode(JFrame frame);
    public static native void setDarkMode(JFrame frame);
    public static native void setLightMode(JFrame frame);
    public static native void setMode(JFrame frame, boolean isDarkMode);

    private JFrameTitlebar() {}
}