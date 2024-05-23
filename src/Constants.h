#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <pgmspace.h>

static constexpr char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
redacted)EOF";

// Device Certificate
static constexpr char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
redacted
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static constexpr char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
redacted
-----END RSA PRIVATE KEY-----
)KEY";

class Constants{
    public:
    double Target = 0;
    double Temp1Avg = 0;
    double Probe1Avg = 0;
    double Probe2Avg = 0;
    double PIDOutput = 0;
    double resistance = 6860;
    double mainProbeOffset = -25;
    double probe1Offset = -1;
    double probe2Offset = 8;
    double AggressiveKP = 4, AggressiveKI = 0.2, AggressiveKD = 1;
    double ConservativeKP = 5.9, ConservativeKI = 1.235, ConservativeKD = 0.6;
    int GrillMode = 0;
    double U = 0.15;
    std::string CookName = "Cook";
    bool augerOn = false;
    bool fanOn = false;
    bool igniterOn = false;
};

extern Constants Consts;

#endif
