typedef struct Mode
{
    char *Name;
    bool fanOn;
    bool augerOn;
    bool igniterOn;
    float cycleTime;
    float u;
};
// Startup, Smoke, Ignite, Hold, Shutdown, Off;

class Modes
{
public:
    Mode Startup = {
        "Startup",
        true,
        true,
        true,
        60,
        0.25};
    Mode Smoke = {
        "Smoke",
        true,
        true,
        false,
        60,
        0.25};
    Mode Ignite = {
        "Ignite",
        true,
        true,
        true,
        60,
        0.25};
    Mode Hold = {
        "Hold",
        true,
        true,
        false,
        20,
        0.15};
    Mode Shutdown = {
        "Shutdown",
        true,
        false,
        false,
        0,
        0};
    Mode Off = {
        "Off",
        false,
        false,
        false,
        0,
        0};
    Mode DebugFan = {
        "DebugFan",
        true,
        false,
        false,
        0,
        0};
    Mode DebugAuger = {
        "DebugAuger",
        false,
        true,
        false,
        0,
        0};
    Mode DebugIgniter = {
        "DebugIgniter",
        false,
        false,
        true,
        0,
        0};

    Mode DebugAll = {
        "DebugAll",
        true,
        true,
        true,
        0,
        0
    };
};

extern Modes ModeSelect;
