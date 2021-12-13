# JFrame-Titlebar
[![Github issues](https://img.shields.io/github/issues/Degubi/JFrame-Titlebar?label=Issues&style=plastic&logo=github)](https://github.com/Degubi/JFrame-Titlebar/issues)
[![Dependencies](https://img.shields.io/badge/Dependencies-0-green?style=plastic&logo=Java)](https://github.com/Degubi/JFrame-Titlebar/blob/master/pom.xml)

## Installation

**Maven dependency:** (via Github Packages)

```xml
<repository>
    <id>github</id>
    <url>https://maven.pkg.github.com/Degubi/jframe-titlebar</url>
</repository>

<dependency>
    <groupId>degubi</groupId>
    <artifactId>jframe-titlebar</artifactId>
    <version>1.0.0</version>
</dependency>
```


**Jar file:**
<br><br>
Jar file downloads are available under 'Packages'

## Usage
All functions are found in a single class: JFrameTitlebar<br>

```java
var frame = new JFrame("Hi");

frame.setSize(800, 600);
frame.setLocationRelativeTo(null);
frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

// This next line is important, because the functions found in JFrameTitlebar only work if the frame is already visible
frame.setVisible(true);

JFrameTitlebar.setDarkMode(frame);  // Sets the titlebar theme to dark
JFrameTitlebar.setLightMode(frame); // Sets the titlebar theme to light
```

## Example with a titlebar theme toggle button

```java
public final class Main {

    public static void main(String[] args) {
        var frame = new JFrame("Hi");

        var toggleButton = new JButton("Toggle");
        toggleButton.addActionListener(e -> JFrameTitlebar.setMode(frame, !JFrameTitlebar.isDarkMode(frame)));

        frame.setContentPane(toggleButton);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
```

## Contributing

Feedback, bug reports and enhancements are always welcome.
