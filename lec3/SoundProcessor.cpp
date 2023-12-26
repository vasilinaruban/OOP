#include "SoundProcessor.h"

void MuteCommand::process(WavFile &wav) {
    int sampleRate = 44100;
    int channels = 1;
    int samplesToMute = (this->endSeconds - this->startSeconds) * sampleRate;

    int startIndex = this->startSeconds * sampleRate * channels + 1024;
    int endIndex = startIndex + samplesToMute * channels;

    for (int i = startIndex; i < endIndex && i < (wav.data.size()); i++)
        wav.data[i] = 0;
}

void MixCommand::process(WavFile &wav) {
    int sampleRate = 44100;
    int channels = 1;
    int insertStartIndex = insertStartSeconds * sampleRate * channels + 1024;

    for (int i = 0; i < addStream.data.size() && i + insertStartIndex < wav.data.size(); i++)
        wav.data[i + insertStartIndex] = (wav.data[i + insertStartIndex] + addStream.data[i]);
}

void ReverseCommand::process(WavFile &wav) {
    int sampleRate = 44100;
    int channels = 1;
    int startSample = this->startSeconds * sampleRate * channels + 1024;
    int endSample = this->endSeconds * sampleRate * channels + 1024;

    if (startSample < 0 || startSample >= wav.data.size() || endSample < 0 || endSample >= wav.data.size()) {
        cerr << "Incorrect positions for playing in reverse." << endl;
        return;
    }

    for (int i = 0; i <= (endSample - startSample) / 2; i++) {
        int16_t buf;
        buf = wav.data[startSample + i];
        wav.data[startSample + i] = wav.data[endSample - i];
        wav.data[endSample - i] = buf;
    }
}