#include <windows.h>
#include <stdio.h>

int main(void)
{
    DEVMODE current = {0};
    current.dmSize = sizeof(current);

    // Get current display settings
    if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &current))
    {
        printf("Failed to get current display settings.\n");
        return 1;
    }

    DWORD originalHz = current.dmDisplayFrequency;

    printf("Current refresh rate: %lu Hz\n", originalHz);

    // Pick a temporary refresh rate
    DWORD temporaryHz = 60;

    if (originalHz == temporaryHz)
    {
        temporaryHz = 120;
    }

    DEVMODE temp = current;
    temp.dmDisplayFrequency = temporaryHz;
    temp.dmFields = DM_DISPLAYFREQUENCY;

    printf("Switching to %lu Hz...\n", temporaryHz);

    LONG result = ChangeDisplaySettings(&temp, CDS_FULLSCREEN);

    if (result != DISP_CHANGE_SUCCESSFUL)
    {
        printf("Failed to change refresh rate. Error code: %ld\n", result);
        return 1;
    }

    // Give Windows/display time to reset
    Sleep(2000);

    printf("Switching back to %lu Hz...\n", originalHz);

    DEVMODE restore = current;
    restore.dmDisplayFrequency = originalHz;
    restore.dmFields = DM_DISPLAYFREQUENCY;

    result = ChangeDisplaySettings(&restore, CDS_FULLSCREEN);

    if (result != DISP_CHANGE_SUCCESSFUL)
    {
        printf("Failed to restore refresh rate. Error code: %ld\n", result);
        return 1;
    }

    printf("Done.\n");

    return 0;
}