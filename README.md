# Display Fixer

A small Windows C utility that resets the primary display by temporarily changing its refresh rate, waiting two seconds, and restoring the original refresh rate.

The temporary rate is 60 Hz, or 120 Hz if the display is already running at 60 Hz. If the display does not support the temporary rate, the program reports an error and exits.

## Build

With MinGW GCC on Windows:

```powershell
gcc refresh.c -o refresh.exe -luser32
```

Or from a Visual Studio Developer Command Prompt:

```bat
cl refresh.c user32.lib /Fe:refresh.exe
```

## Run

```powershell
.\refresh.exe
```

The screen may briefly flicker during the change. If restoring the original refresh rate fails, restore it through Windows Display settings.

Compiled executables and local editor settings are excluded from version control.
