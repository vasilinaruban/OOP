#pragma once
#include "WavFile.h"

class SoundProcessor {
public:
    virtual void process(WavFile& wav) = 0;
    virtual ~SoundProcessor() = default;
};

class MuteCommand : public SoundProcessor {
public:
    MuteCommand(int startSeconds, int endSeconds)
            : startSeconds(startSeconds), endSeconds(endSeconds) {}

    void process(WavFile& wav) override;

private:
    int startSeconds;
    int endSeconds;
};

class ReverseCommand : public SoundProcessor {
public:
    ReverseCommand(int startSeconds, int endSeconds)
            : startSeconds(startSeconds), endSeconds(endSeconds) {}

    void process(WavFile& wav) override;

private:
    int startSeconds;
    int endSeconds;
};

class MixCommand : public SoundProcessor {
public:
    WavFile addStream;
    int insertStartSeconds;
    MixCommand(WavFile  additionalStream, int insertStartSeconds) : addStream(std::move(additionalStream)), insertStartSeconds(insertStartSeconds) {}

    void process(WavFile& wav) override;

};

